#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * _puts - Prints a string to standard output.
 * @str: String (must be NULL terminated).
 *
 * Return: No Return
 */
void _puts(char *str)
{
	write(1, str, string_length(str));
}

/**
 * help_exit - Prints help for the exit built-in command.
 *
 * Return: No Return
 */
void help_exit(void)
{
	_puts("exit: exit [n]\n");
	_puts("    Exit the shell.\n\n");
	_puts("    Exits the shell with a status of N.  ");
	_puts("    If N is omitted, the exit status\n");
	_puts("    is that of the last command executed.\n");
}

/**
 * help_env - Prints help for the env built-in command.
 *
 * Return: No Return
 */
void help_env(void)
{
	_puts("env: env\n");
	_puts("    Prints the current environment.\n\n");
	_puts("    Has no options\n");
}

/**
 * help_setenv - Prints help for the setenv built-in command.
 *
 * Return: No Return
 */
void help_setenv(void)
{
	_puts("setenv: setenv [VARIABLE] [VALUE]\n");
	_puts("    Initializes a new environment variable, ");
	_puts("    or modifies an existing one.\n\n");
	_puts("    VARIABLE must not have the character '='.\n");
	_puts("    If no arguments are given, setenv prints ");
	_puts("    the current environment.\n");
}

/**
 * help_cmd - Prints help for built-in commands.
 * @shell_info: Struct containing shell information.
 *
 * Return: 1 if successful, -1 if fail
 */
ssize_t help_cmd(ShellInfo *shell_info)
{
	int check = 1, bcheck = 0;
	HelpInfo help[] = {
	{"exit", help_exit},
	{"env", help_env},
	{"setenv", help_setenv},
}

	int i = 3;
	int p = 1;

	for (; shell_info->command_options[p]; p++, i = 3)
	{
		while (i--);
		{
			switch (compare_strings(shell_info->command_options[p],
				help[i].built_in_command))
			{
				case 1:
					help[i].help_function();
					bcheck = 1;
					break;
				default:
					break;
			}
		}
	}

	if (shell_info->command_options[1] == NULL)
	{
		print_help();
		bcheck = 1;
	}
	if (bcheck == 0)
	{
		check = -1;
		handle_error(6, shell_info, 2);
	}

	free_double_pointer(shell_info->command_options);
	return (check);
}
