#include "shell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * auxiliary_cd_2 - Auxiliary function for the cd built-in command
 *
 * @shell_info: Structure containing shell information
 * @current_directory: The current directory
 * Return: Pointer to HOME or NULL if fail
 */
char *auxiliary_cd_2(ShellInfo *shell_info, char *current_directory)
{
	char *home, *directory = NULL;

	(void)current_directory;
	home = _get_environment_variable("HOME", *(shell_info->environment_copy));
	if (home)
		directory = home + 5;
	return (directory);
}

/**
 * auxiliary_cd - Auxiliary function for the cd built-in command
 *
 * @shell_info: Structure containing shell information
 * @current_directory: The current directory
 * Return: Pointer to directory or NULL if fail
 */
char *auxiliary_cd(ShellInfo *shell_info, char *current_directory)
{
	char *oldpwd2 = NULL, *oldpwd = NULL, *directory = NULL;

	switch (shell_info->command_options[1] != NULL &&
		shell_info->command_options[2] != NULL)
	{
		case 1:
			write(2, "cd: too many arguments\n", 23);
			*(shell_info->exit_number) = 2;
			free(shell_info->command_options);
			free(current_directory);
			return (directory);
		default:
			oldpwd2 = _str_duplicate(_get_environment_variable(
				"OLDPWD", *(shell_info->environment_copy)));
			if (oldpwd2)
				oldpwd = _str_duplicate(oldpwd2 + 7), free(oldpwd2);
			if (!oldpwd2)
				oldpwd = _str_duplicate(current_directory);
			directory = oldpwd;
			return (directory);
	}
}
