#include "shell.h"
#include <unistd.h>

/**
 * _get_environment_variable - Get the value of an environment variable
 * @name: Name of the environment variable
 * @env: Array of environment variables
 * Return: Value of the environment variable or NULL if not found
 */
char *_get_environment_variable(const char *name, char **env)
{
	size_t check;
	size_t j;
	size_t name_length;
	int i;

	name_length = 0;
	if (!env || !name)
		return (NULL);

	while (name[name_length] != '\0')
		name_length++;

	for (i = 0; env[i] != NULL; i++)
	{
		check = 0;
		j = 0;
		while (j < name_length && env[i][j] != '\0')
		{
			if (env[i][j] == name[j])
				check++;
			j++;
		}
		if (check == name_length && env[i][check] == '=')
			return (env[i]);
	}
	/* Return NULL if the environment variable is not found */
	return (NULL);
}
