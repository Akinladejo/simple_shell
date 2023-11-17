#include "shell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * get_user_input - Gets user input from the command line.
 *
 * @buffer_size: Pointer to the size of the buffer.
 * @buffer: Pointer to the buffer storing the user input.
 * @shell_info: Pointer to ShellInfo structure containing shell information.
 *
 * Return: Double pointer to the parsed command or NULL if no valid input.
 */
char **get_user_input(size_t *buffer_size, char **buffer, ShellInfo *shell_info)
{
	ssize_t characters;
	char **command;
	int exit_number;

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);
	characters = getline(buffer, buffer_size, stdin);
	if (characters == -1)
	{
		exit_number = shell_info->exit_number[0];
		free(*buffer);
		if (*(shell_info->environment_copy))
			free_double_pointer(*(shell_info->environment_copy));
		free(shell_info);
		if (isatty(STDIN_FILENO))
			write(1, "\n", 1);
		exit(exit_number);
	}
	if (**buffer == '#' || !characters || **buffer == '\n')
		return (NULL);
	*buffer = remove_comments(*buffer);
	command = get_parameters(*buffer, shell_info);
	return (command);
}

/**
 * check_input - Check for input after the shell prompt
 * @argument_count: Count of main arguments
 * @arguments: Main arguments
 * @buffer_size: Size of the buffer in the prompt
 * @buffer: Buffer in the prompt
 * @shell_info: Struct containing shell information
 *
 * Return: On success, returns a command array. On error, exits the program.
 */
char **check_input(int argument_count, char **arguments, size_t *buffer_size,
char **buffer, ShellInfo *shell_info)
{
	char **command;
	
	switch (argument_count)
	{
		case 1:
			command = get_user_input(buffer_size, buffer, shell_info);
			break;
		default:
			command = malloc(sizeof(char *) * argument_count);
			if (!command)
			{
				handle_error(7, shell_info, 1);
				exit(1);
			}
			command[argument_count - 1] = '\0';
			while (argument_count--)
				command[argument_count - 1] = arguments[argument_count];
			break;
	}
	return (command);
}

/**
 * remove_comments - Removes comments from a command line
 *
 * @string: String to operate
 *
 * Return: Pointer to the modified string.
 */
char *remove_comments(char *string)
{
	char *original = string;

	while (string && *string)
	{
		switch (*string)
		{
			case '#':
				if (*(string - 1) == ' ')
				{
					*string = '\0';
					return (original);
				}
				break;
			default:
				break;
		}
		string++;
	}
	return (original);
}
