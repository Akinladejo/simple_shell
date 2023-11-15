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
 *
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
 *
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

/**
 * cd_command - Built-in command cd
 *
 * @shell_info: Structure containing shell information
 *
 * Return: 1 if successful, -1 if fail
 */
ssize_t cd_command(ShellInfo *shell_info)
{
	char *current_directory = getcwd(NULL, 4096);

	if (!current_directory)
	{
		handle_error(4, shell_info, 2);
		free(shell_info->command_options);
		return (-1);
	}

	char *directory = determine_directory(shell_info, current_directory);

	if (!directory)
	{
		free(shell_info->command_options);
		free(current_directory);
		return (1);
	}

	int result = change_directory(directory, shell_info);

	if (result == 0 && shell_info->check_minus == 1)
	{
		write(1, directory, _string_length(directory));
		write(1, "\n", 1);
	}

	handle_directory_change_result(result, shell_info, current_directory,
		directory);

	free_resources(shell_info, current_directory, directory);

	return (shell_info->exit_code);
}

/**
 * determine_directory - Determine the target directory for the cd command
 *
 * @shell_info: Structure containing shell information
 * @current_directory: The current directory
 *
 * Return: The target directory
 */
char *determine_directory(ShellInfo *shell_info, const char *current_directory)
{
	char *directory = NULL;

	if (!shell_info->command_options[1] ||
		!_compare_strings(shell_info->command_options[1], "~"))
	{
		directory = auxiliary_cd_2(shell_info, current_directory);
	}
	else
	{
		if (!_compare_strings(shell_info->command_options[1], "-"))
		{
			directory = auxiliary_cd(shell_info, current_directory);
			shell_info->check_minus = 1;
		}
		else
		{
			directory = shell_info->command_options[1];
		}
	}

	return (directory);
}

/**
 * change_directory - Change the current working directory
 *
 * @directory: The target directory
 * @shell_info: Structure containing shell information
 *
 * Return: 0 on success, -1 on failure
 */
int chang_directory(const char *directory, ShellInfo *shell_info)
{
	int result = chdir(directory);

	if (result != 0)
	{
		handle_error(4, shell_info, 2);
		shell_info->exit_code = -1;
	}
	else
	{
		update_environment_variables(shell_info, directory);
	}

	return (result);
}

/**
 * update_environment_variables - Update env var after directory change
 *
 * @shell_info: Structure containing shell information
 * @directory: The target directory
 */
void update_environment_variables(ShellInfo *shell_info, const char *directory)
{
	char **new_environment = set_environment_variable(*(shell_info->environment_copy),
	"PWD", directory, shell_info);
	*(shell_info->environment_copy) = new_environment;

	new_environment = set_environment_variable(*(shell_info->environment_copy), "OLDPWD",
		shell_info->current_directory, shell_info);
	*(shell_info->environment_copy) = new_environment;

	shell_info->current_directory = directory;
}

/**
 * handle_directory_change_result - Handle the result of a directory change
 *
 * @result: The result of the directory change
 * @shell_info: Structure containing shell information
 * @current_directory: The current directory
 * @directory: The target directory
 */
void handle_directory_change_result(int result, ShellInfo *shell_info,
const char *current_directory, const char *directory)
{
	if (result != 0)
	{
		handle_error(4, shell_info, 2);
		shell_info->exit_code = -1;
	}
	else
	{
		update_environment_variables(shell_info, directory);
	}
}

/**
 * free_resources - Free allocated resources
 *
 * @shell_info: Structure containing shell information
 * @current_directory: The current directory
 * @directory: The target directory
 */
void free_resources(ShellInfo *shell_info, char *current_directory,
char *directory)
{
	free(shell_info->command_options);
	free(current_directory);
	free(shell_info->oldpwd);

	if (shell_info->check_minus == 1)
	{
		free(directory);
	}
}
