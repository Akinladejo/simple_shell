#include "shell.h"
#include <unistd.h>

/**
 * _get_environment_variable - Get the value of an environment variable
 *
 * @name: Name of the environment variable
 * @env: Array of environment variables
 * Return: Value of the environment variable or NULL if not found
 */
char *_get_environment_variable(const char *name, char **env)
{
	if (!env || !name)
		return (NULL);

	size_t name_length = 0;
	while (name[name_length] != '\0')
		name_length++;

	for (int i = 0; env[i] != NULL; i++) {
		size_t check = 0;
		size_t j = 0;

		while (j < name_length && env[i][j] != '\0') {
			if (env[i][j] == name[j])
				check++;
			j++;
		}

		if (check == name_length && env[i][check] == '=')
			return (env[i]);
	}

	return (NULL);
}
