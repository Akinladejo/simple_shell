#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _copy_double_pointer - copies an array of strings (double pointer)
 * @p: double pointer to copy
 * @new_size: size of copy
 * @jump: value that must be skipped in copy
 *
 * Return: Pointer malloec
 */
char **_copy_double_pointer(char **p, int new_size, int jump)
{
	char **copy;
	int i, j, csize;

	csize = new_size;
	copy = malloc(sizeof(char *) * (csize + 1));
	if (copy == NULL)
		return (NULL);
	for (i = 0, j = 0; j < csize; i++, j++)
	{
		if (i == jump)
			i++;
		copy[j] = _str_duplicate(p[i]);
		if (copy[j] == NULL)
		{
			j--;
			for (; j >= 0; j--)
				free(copy[j]);
			free(copy);
			return (NULL);
		}
	}
	copy[new_size] = NULL;
	return (copy);
}

/**
 * _unset_environment_variable - unsets an environmental variable
 * @env: array of env variables
 * @variable: env variable to unset
 * @shell_info: struct with shell info
 *
 * Return: Modified environment array on success, NULL on error
 */
char **_unset_environment_variable(char **env, const char *variable,
ShellInfo *shell_info)
{
	int i, j, check, l = 0, lenv = 0, found = 0;
	char **copy;

	shell_info->unset_environment[0] = 0;
	if (!env || string_length(variable) == 0 || variable == NULL)
	{
		handle_error(3, shell_info, (!env) ? 1 : 2);
		return (NULL);
	}
	l = string_length(variable);
	lenv = string_array_length(env);
	for (i = 0; env[i] != NULL; i++)
	{
		for (check = 0, j = 0; j < l && env[i][j] != '\0'; j++)
		{
			if (variable[j] == '=')
			{
				handle_error(3, shell_info, 3);
				return (NULL);
			}
			if (env[i][j] == variable[j])
				check++;
		}
		if (check == l && env[i][check] == '=')
		{
			/* Found env to erase */
			found = 1;
			if ((lenv - 1) != 0)
			{
				copy = _copy_double_pointer(env, lenv - 1, i);
				if (copy == NULL)
				{
					handle_error(7, shell_info, 1);
					return (NULL);
				}
			}
			else
			{
				shell_info->unset_environment[0] = 1;
				copy = NULL;
			}
			free_double_pointer(env);
			return (copy);
		}
	}
	if (found == 0)
	{
		write(2, "VARIABLE not found\n", 19);
		return (NULL);
	}
	return (env);
}
