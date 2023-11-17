#include "shell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * cd_command - Built-in command cd
 *
 * @shell_info: Structure containing shell information
 * Return: 1 if successful, -1 if fail
 */
ssize_t cd_command(ShellInfo *shell_info)
{
	char *current_directory = NULL, *directory = NULL, **new_environment,
	*oldpwd = NULL;
	int exit_code = 1, check = 1, check_minus = 0;

	current_directory = getcwd(NULL, 4096);
	if (!current_directory)
		return ((handle_error(4, shell_info, 2),
			free(shell_info->command_options), -1));
	switch (!shell_info->command_options[1] ||
		(!compare_strings(shell_info->command_options[1], "~")))
	{
		case 1:
			directory = auxiliary_cd_2(shell_info, current_directory);
			if (!directory)
				return (free(shell_info->command_options), free(current_directory),
					1);
			break;
		default:
			if (!compare_strings(shell_info->command_options[1], "-"))
			{
				directory = auxiliary_cd(shell_info, current_directory);
				if (!directory)
					return (free(shell_info->command_options),
						free(current_directory), 1);
				check_minus = 1;
			}
			else
			{
				directory = shell_info->command_options[1];
			}
	}

	if (directory)
		check = chdir(directory);
	if (check == 0 && check_minus == 1)
		write(1, directory, string_length(directory)), write(1, "\n", 1);

	switch (check != 0)
	{
		case 1:
			handle_error(4, shell_info, 2);
			exit_code = -1;
			break;
		default:
			new_environment = set_environment_variable(
				*(shell_info->environment_copy), "PWD", directory, shell_info);
			*(shell_info->environment_copy) = new_environment;
			new_environment =
				set_environment_variable(*(shell_info->environment_copy), "OLDPWD",
				current_directory, shell_info);
			*(shell_info->environment_copy) = new_environment;
	}
	free(shell_info->command_options);
	free(current_directory);
	free(oldpwd);
	if (check_minus == 1)
	{
		free(directory);
	}
	return (exit_code);
}
