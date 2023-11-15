#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * free_double_pointer - Frees a double pointer.
 * @pointer: The double pointer to be freed.
 *
 * This function frees the memory occupied by a double pointer.
 * Return: None
 */
void free_double_pointer(char **pointer)
{
	int i; /* Move declaration to the beginning */

	if (!pointer)
		return;

	for (i = 0; pointer[i] != NULL; i++)
		free(pointer[i]);

	free(pointer);
}

/**
 * copy_double_pointer - Copies a double pointer to a new size.
 * @pointer: The original double pointer.
 * @old_size: The old size of the double pointer.
 * @new_size: The new size of the double pointer.
 *
 * This function copies a double pointer to a new size.
 * Returns the copied double pointer or NULL on failure.
 */
char **copy_double_pointer(char **pointer, int old_size, int new_size)
{
	int i; /* Move declaration to the beginning */
	int copy_size = (new_size < old_size) ? new_size : old_size;
	char **copy = malloc(sizeof(char *) * (copy_size + 1));

	if (!copy)
		return NULL;

	for (i = 0; i < copy_size; i++)
	{
		copy[i] = _str_duplicate(pointer[i]);

		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return NULL;
		}
	}

	copy[new_size] = NULL;
	return copy;
}

/**
 * string_array_length - Calculates the length of a string array.
 * @array: The string array.
 *
 * This function calculates the length of a string array.
 * Return: The length of the string array.
 */
int string_array_length(char **array)
{
	int length; /* Move declaration to the beginning */

	if (array == NULL)
		return 0;

	for (length = 0; array[length] != NULL; length++)
		;

	return length;
}

/**
 * set_environment_variable - Sets an environment variable.
 * @env: The environment array.
 * @variable: The variable to be set.
 * @value: The value to set for the variable.
 * @shell_info: The shell information.
 *
 * This function sets an environment variable.
 * Returns the modified environment array or NULL on failure.
 */
char **set_environment_variable(char **env, char *variable, char *value, ShellInfo *shell_info)
{
	int len_variable;
	int len_env;
	char *env_join2;
	int i;
	char *env_join;
	
	if (!variable || string_length(variable) == 0)
		return (handle_error(3, shell_info, 1), NULL);

	int len_variable = string_length(variable);
	int len_env = string_array_length(env);
	

	char *env_join2 = concatenate_strings(variable, "=");
	if (!env_join2)
		return (handle_error(3, shell_info, 1), NULL);

	char *env_join = concatenate_strings(env_join2, value);
	free(env_join2);

	if (!env_join)
		return (handle_error(3, shell_info, 1), NULL);

	for (i = 0; env && env[i] != NULL; i++)
	{
		int check = 0;
		int j;
		for (j = 0; j < len_variable && env[i][j] != NULL; j++)
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

			if (!copy_dup)
				return (handle_error(3, shell_info, 1), NULL);

			return (env[i] = copy_dup, env);
		}
	}

	char **copy;
	
	char **copy = copy_double_pointer(env, len_env, len_env + 1);
	free_double_pointer(env);

	if (!copy)
		return (free(env_join), handle_error(3, shell_info, 1), NULL);

	env = copy;
	char *copy_dup = _str_duplicate(env_join);
	free(env_join);

	if (!copy_dup)
		return (handle_error(3, shell_info, 1), NULL);

	return (env[len_env] = copy_dup, env);
}
