#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * free_double_pointer - Frees a double pointer.
 * @pointer: The double pointer to be freed.
 * Return: free dbp
 */
void free_double_pointer(char **pointer)
{
	if (!pointer)
		return;

	for (int i = 0; pointer[i] != NULL; i++)
		free(pointer[i]);

	free(pointer);
}

/**
 * copy_double_pointer - Copies a double pointer to a new size.
 * @pointer: The original double pointer.
 * @old_size: The old size of the double pointer.
 * @new_size: The new size of the double pointer.
 * Return: The copied double pointer or (NULL) on failure.
 */
char **copy_double_pointer(char **pointer, int old_size, int new_size)
{
	switch (old_size == new_size)
	{
	case 1:
		return (NULL);
	}

	int copy_size = (new_size < old_size) ? new_size : old_size;
	char **copy = malloc(sizeof(char *) * (copy_size + 1));

	switch (!!pointer)
	{
	case 1:
		for (int i = 0; i < copy_size; i++)
		{
			copy[i] = _str_duplicate(pointer[i]);

			switch (!copy[i])
			{
			case 1:
				while (--i >= 0)
					free(copy[i]);
				free(copy);
				return (NULL);
			}
		}
	}

	copy[new_size] = NULL;
	return (copy);
}

/**
 * string_array_length - Calculates the length of a string array.
 * @array: The string array.
 * Return: The length of the string array.
 */
int string_array_length(char **array)
{
	if (!array)
		return (0);

	int length;
	for (length = 0; array[length] != NULL; length++)
		;

	return (length);
}

/**
 * set_environment_variable - Sets an environment variable.
 * @env: The environment array.
 * @variable: The variable to be set.
 * @value: The value to set for the variable.
 * @shell_info: The shell information.
 * Return: The modified environment array or (NULL) on failure.
 */
char **set_environment_variable(char **env, char *variable, char *value, ShellInfo *shell_info)
{
	if (!variable || string_length(variable) == 0)
		return (handle_error(3, shell_info, 1), NULL);

	char *env_join2 = concatenate_strings(variable, "=");
	switch (!!env_join2) {
	case 0:
		return (handle_error(3, shell_info, 1), NULL);
	}

	char *env_join = concatenate_strings(env_join2, value);
	free(env_join2);

	switch (!!env_join)
	{
	case 0:
		return (handle_error(3, shell_info, 1), NULL);
	}

	int len_variable = string_length(variable);
	int len_env = string_array_length(env);

	for (int i = 0; env && env[i] != NULL; i++)
	{
		int check = 0;
		for (int j = 0; j < len_variable && env[i][j] != NULL; j++)
		{
			if (variable[j] == '=')
				return (free(env_join), handle_error(3, shell_info, 2), NULL);

			if (env[i][j] == variable[j])
				check++;
		}

		if (check == len_variable && env[i][check] == '=')
		{
			free(env[i]);
			char *copy_dup = _str_duplicate(env_join);
			free(env_join);

			switch (!copy_dup)
			{
			case 1:
				return (handle_error(3, shell_info, 1), NULL);
			}

			return (env[i] = copy_dup, env);
		}
	}

	char **copy = copy_double_pointer(env, len_env, len_env + 1);
	free_double_pointer(env);

	switch (!copy)
	{
	case 1:
		return (free(env_join), handle_error(3, shell_info, 1), NULL);
	}

	env = copy;
	char *copy_dup = _str_duplicate(env_join);
	free(env_join);

	switch (!copy_dup)
	{
	case 1:
		return (handle_error(3, shell_info, 1), NULL);
	}

	return (env[len_env] = copy_dup, env;)
}
