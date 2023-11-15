#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * unset_environment_variable - Unsets an environmental variable
 *
 * @env: Array of environment variables
 * @variable: Environment variable to unset
 * @shell_info: Struct with shell info
 *
 * Return: Modified environment array on success, NULL on error
 */
char **unset_environment_variable(char **env, const char *variable, ShellInfo *shell_info)
{
	if (!env || !variable)
	{
		handle_error(3, shell_info, 1);
		return (NULL);
	}

	size_t var_length = string_length(variable);
	size_t env_length = string_array_length(env);

	size_t i, j;
	int found = 0;

	for (i = 0; i < env_length; i++)
	{
		int check = 0;

		for (j = 0; j < var_length && env[i][j] != '\0'; j++)
		{
			if (variable[j] == '=' || env[i][j] != variable[j])
			{
				check = 0;
				break;
			}
			else
			{
				check++;
			}
		}

		if (check == var_length && env[i][check] == '=')
		{
			found = 1;
			break;
		}
	}

	switch (found)
	{
	case 0:
		write(2, "VARIABLE not found\n", 19);
		return (NULL);

	case 1:
		char **copy = NULL;

		if (env_length > 1)
		{
			copy = copy_double_pointer(env, env_length - 1, i);

			if (!copy)
			{
				handle_error(7, shell_info, 1);
				return (NULL);
			}
		}
		else
		{
			copy = NULL;
			shell_info->unset_environment[0] = 1;
		}

		free_double_pointer(env);
		return (copy);

	default:
		handle_error(8, shell_info, 1);
		return (NULL);
	}
}
