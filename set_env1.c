#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * search_environment_variable - Search for an existing environment variable.
 * @env: Pointer to an array of strings representing the environment variables.
 * @variable: The name of the environment variable to search for.
 *
 * Return: Index of the found variable or -1 if not found.
 */
int search_environment_variable(char **env, char *variable)
{
	int i, j, check, len_variable, len_env;

	len_variable = string_length(variable);
	len_env = string_array_length(env);

	for (i = 0; env && env[i] != NULL; i++)
	{
		check = 0;
		for (j = 0; j < len_variable && env[i][j] != '\0'; j++)
		{
			if (variable[j] == '=')
				return (-1);
			if (env[i][j] == variable[j])
				check++;
		}

		if (check == len_variable && env[i][check] == '=')
			return (i);
	}

	return (-1);
}

/**
 * set_environment_variable - Set or update an environment variable.
 * @env: Pointer to an array of strings representing the environment variables.
 * @variable: The name of the environment variable to set.
 * @value: The value to assign to the environment variable.
 * @shell_info: Information about the shell (not provided in the code).
 *
 * Return: Pointer to the modified or new environment array, or NULL on error.
 */
char **set_environment_variable(char **env, char *variable, char *value,
                                ShellInfo *shell_info)
{
	int index;
	char *env_join2, *env_join, **copy, *copy_dup;

	if (!variable || string_length(variable) == 0)
		return (handle_error(3, shell_info, 1), NULL);

	env_join2 = concatenate_strings(variable, "=");
	if (!env_join2)
		return (handle_error(3, shell_info, 1), NULL);

	env_join = concatenate_strings(env_join2, value);
	free(env_join2);
	if (!env_join)
		return (handle_error(3, shell_info, 1), NULL);

	index = search_environment_variable(env, variable);
	if (index != -1)
	{
		free(env[index]);
		copy_dup = _str_duplicate(env_join);
		free(env_join);
		if (!copy_dup)
			return (handle_error(3, shell_info, 1), NULL);

		return (env[index] = copy_dup, env);
	}

	copy = copy_double_pointer(env, string_array_length(env), string_array_length(env) + 1);
	free_double_pointer(env);
	if (!copy)
		return (free(env_join), handle_error(3, shell_info, 1), NULL);

	env = copy;
	copy_dup = _str_duplicate(env_join);
	free(env_join);
	if (!copy_dup)
		return (handle_error(3, shell_info, 1), NULL);

	return (env[string_array_length(env) - 1] = copy_dup, env);
}
