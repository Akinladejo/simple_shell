#include "shell.h"
#include "builtin22.c"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * cd_command - Change the current directory based on the provided arguments.
 * @shell_info: Pointer to the ShellInfo struct containing shell information.
 *
 * Return: On success, returns the exit code (1). On failure, returns -1.
 */
ssize_t cd_command(ShellInfo *shell_info)
{
	int exit_code = 1;

	if (!validate_cd_arguments(shell_info))
		return (-1);

	char *current_directory = get_current_directory();
	if (!current_directory)
		return (-1);

	char *directory = get_directory(shell_info);
	if (!directory)
	{
		free(current_directory);
		return (-1);
	}

	change_directory(directory);
	update_environment_variables(directory, current_directory);

	cleanup(shell_info, current_directory, directory);

	return (exit_code);
}

/**
 * validate_cd_arguments - Check the number of arguments for the cd command.
 * @shell_info: Pointer to the ShellInfo struct containing shell information.
 *
 * Return: 1 if the number of arguments is valid, 0 otherwise.
 */
int validate_cd_arguments(ShellInfo *shell_info)
{
	if (shell_info->command_options[1] && !shell_info->command_options[2])
	{
		return (1);
	}
	else
	{
		write(2, "cd: too many arguments\n", 23);
		*(shell_info->exit_number) = 2;
		free(shell_info->command_options);
		return (0);
	}
}

/**
 * get_current_directory - Get the current working directory.
 *
 * Return: On success, returns a pointer to the current directory string.
 * On failure, returns NULL.
 */
char *get_current_directory(void)
{
	char *current_directory = getcwd(NULL, 4096);
	if (!current_directory)
	{
		handle_error(4, shell_info, 2);
		return (NULL);
	}

	return (current_directory);
}
