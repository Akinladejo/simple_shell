#include "shell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * exit_command - Built-in command to exit the shell
 * @shell_info: Struct containing shell information
 *
 * Return: (-1) if error, exit value otherwise
 */
ssize_t exit_command(ShellInfo *shell_info)
{
	long valueToExit;

	switch (shell_info->command_options[1] == NULL ||
		is_number(shell_info->command_options[1]))
	{
	case 1:
		valueToExit =
		    convert_to_integer(shell_info->command_options[1]);

		if (valueToExit >= 0 && valueToExit < INT_MAX)
		{
			if (valueToExit > 255)
				valueToExit %= 256;
			if (shell_info->command_options[1] == NULL)
				valueToExit = *(shell_info->exit_number);
			free(*(shell_info->command_options));
			free(shell_info->command_options);
			if (*(shell_info->environment_copy))
				free_double_pointer(
				    *(shell_info->environment_copy));
			free(shell_info);
			exit(valueToExit);
		}
		break;

	default:
		/* Error handling */
		handle_error(2, shell_info, 2);
		free(shell_info->command_options);
		return (-1);
	}

	return (-1);
}

/**
 * env_command - Built-in command to print the environment
 * @shell_info: Struct containing shell information
 *
 * Return: (1) if successful, (-1) on failure
 */
ssize_t env_command(ShellInfo *shell_info)
{
	char **envCopy;
	int check = 1;

	if (*(shell_info->environment_copy) == NULL)
	{
		write(2, "Environment is Null, Can't Print it\n", 36);
		*(shell_info->exit_number) = 2;
		free(shell_info->command_options);
		return (-1);
	}

	envCopy = *(shell_info->environment_copy);

	switch (shell_info->command_options[1] == NULL)
	{
	case 1:
		for (; envCopy && *envCopy; envCopy++)
		{
			write(1, *envCopy, string_length(*envCopy));
			write(1, "\n", 1);
		}
		break;

	default:
		handle_error(0, shell_info, 2);
		check = -1;
	}

	free(shell_info->command_options);
	return (check);
}

/**
 * setenv_command - Built-in command to set an environment variable
 * @shell_info: Struct containing shell information
 *
 * Return: (1) if successful, (-1) on failure
 */
ssize_t setenv_command(ShellInfo *shell_info)
{
	char **newEnvironment;
	char *variable = NULL;
	char *value = NULL;

	if (shell_info->command_options[1])
	{
		variable = shell_info->command_options[1];
		if (!shell_info->command_options[2])
		{
			write(2, "Invalid VALUE\n", 14);
			*(shell_info->exit_number) = 2;
			free(shell_info->command_options);
			return (-1);
		}
		else
			value = shell_info->command_options[2];
	}
	if (variable == 0)
	{
		/* Error handling */
		write(2, "Invalid VARIABLE\n", 17);
		*(shell_info->exit_number) = 2;
		free(shell_info->command_options);
		return (-1);
	}

	newEnvironment = set_environment_variable(
	    *(shell_info->environment_copy), variable, value, shell_info);

	if (newEnvironment == 0)
	{
		free(shell_info->command_options);
		return (-1);
	}

	*(shell_info->environment_copy) = newEnvironment;
	free(shell_info->command_options);
	return (1);
}

/**
 * unsetenv_command - Built-in command to unset an environment variable
 * @shell_info: Struct containing shell information
 *
 * Return: (1) if successful, (-1) on failure
 */
ssize_t unsetenv_command(ShellInfo *shell_info)
{
	char **newEnvironment;
	char *variable = NULL;

	if (shell_info->command_options[1])
		variable = shell_info->command_options[1];
	else
	{
		*(shell_info->exit_number) = 2;
		write(2, "Please provide an argument\n", 27);
		return (free(shell_info->command_options), -1);
	}

	switch (variable == 0)
	{
	case 1:
		/* Variable not provided */
		free(shell_info->command_options);
		return (1);

	default:
		newEnvironment = unset_environment_variable(
		    *(shell_info->environment_copy), variable, shell_info);

		if (newEnvironment == 0 &&
		    *(shell_info->unset_environment) == 0)
		{
			/* Error handling */
			free(shell_info->command_options);
			*(shell_info->exit_number) = 2;
			return (-1);
		}

		*(shell_info->environment_copy) = newEnvironment;
		free(shell_info->command_options);
		return (1);
	}
}

/**
 * execute_built_ins - Checks and executes built-in commands
 * @shell_info: Struct containing shell information
 *
 * Return: (1) if successful, (-1) on failure
 */
ssize_t execute_built_ins(ShellInfo *shell_info)
{
	BuiltIn builtIns[] = {
	    {"exit", exit_command},	{"env", env_command},
	    {"setenv", setenv_command}, {"unsetenv", unsetenv_command},
	    {"cd", change_directory},	{"help", help_command}
};

	int i = 6; /* length of builtIns array */
	ssize_t builtCheck = 0;

	while (i--)
	{
		if (compare_strings(shell_info->current_command,
				    builtIns[i].command))
		{
			*(shell_info->error_count) += 1;
			builtCheck = builtIns[i].function(shell_info);
			if (builtCheck == 1)
				*(shell_info->exit_number) = 0;
			return (builtCheck);
		}
	}

	return (0);
}
