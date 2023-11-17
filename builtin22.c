#include "shell.h"
#include "builtin2.c"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * get_directory - Get the directory argument from the command options.
 * @shell_info: Pointer to the ShellInfo struct containing shell information.
 *
 * Return: Pointer to the directory string.
 */
char *get_directory(ShellInfo *shell_info)
{
	if (shell_info->command_options[1])
	{
		return (shell_info->command_options[1]);
	}

	return (NULL);
}

/**
 * change_directory - Change the current working directory.
 * @directory: Pointer to the directory string.
 */
void change_directory(char *directory)
{
	int check = chdir(directory);
	if (check != 0)
	{
		handle_error(4, shell_info, 2);
	}
}

/**
 * update_environment_variables - Update environment variables (PWD and OLDPWD).
 * @directory: Pointer to the new working directory.
 * @current_directory: Pointer to the current working directory.
 */
void update_environment_variables(char *directory, char *current_directory)
{
	char **new_environment;

	new_environment = set_environment_variable(*(shell_info->environment_copy), "PWD", directory, shell_info);
	*(shell_info->environment_copy) = new_environment;
	new_environment = set_environment_variable(*(shell_info->environment_copy), "OLDPWD", current_directory, shell_info);
	*(shell_info->environment_copy) = new_environment;
}

/**
 * cleanup - Free allocated memory and perform cleanup.
 * @shell_info: Pointer to the ShellInfo struct containing shell information.
 * @current_directory: Pointer to the current working directory string.
 * @directory: Pointer to the directory string.
 */
void cleanup(ShellInfo *shell_info, char *current_directory, char *directory)
{
	free(shell_info->command_options);
	free(current_directory);
	free(directory);
}
