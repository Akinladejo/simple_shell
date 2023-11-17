#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH_SEPARATOR ':'

/* Add your Betty-style comments for the missing functions here */

/**
 * _get_environment_variable - Get the value of an environment variable
 * @name: The name of the environment variable
 * @env: The environment variables
 *
 * Return: The value of the env variable if found, or NULL if not found.
 */
char *_get_environment_variable(const char *name, char **env)
{
	int i;

	if (!name || !env)
		return (NULL);

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], name, strlen(name)) == 0 &&
			env[i][strlen(name)] == '=')
		{
			return (env[i] + strlen(name) + 1);
		}
	}
	return (NULL);
}

/**
 * _str_duplicate - Duplicate a string
 * @str: The input string
 *
 * Return: A newly allocated string containing a duplicate of the input string,
 *         or NULL if memory allocation fails.
 */
char *_str_duplicate(const char *str)
{
	size_t len;
	char *dup_str;

	if (!str)
		return (NULL);

	len = strlen(str) + 1;
	dup_str = malloc(len);

	if (!dup_str)
		return (NULL);

	return (strcpy(dup_str, str));
}

/**
 * _string_token - Get the next token in a string
 * @str: The input string, or NULL to continue with the previous string
 * @delim: The delimiter string
 *
 * Return: The next token if found, or NULL if no more tokens are found.
 */
char *_string_token(char *str, const char *delim)
{
	static char *last_str;
	char *token;

	if (!str && !delim)
		return (NULL);

	last_str = NULL;

	if (str)
		last_str = str;

	token = strtok(last_str, delim);
	last_str = NULL;
	return (token);
}

/**
 * concatenate_strings - Concatenate two strings
 * @str1: The first string
 * @str2: The second string
 *
 * Return: A newly allocated string containing the concatenation of the input
 * strings, or NULL if memory allocation fails.
 */
char *concatenate_strings(const char *str1, const char *str2)
{
	size_t len1;
	size_t len2;
	char *result;

	if (!str1 || !str2)
		return (NULL);

	len1 = strlen(str1);
	len2 = strlen(str2);
	result = malloc(len1 + len2 + 1);

	if (!result)
		return (NULL);

	strcpy(result, str1);
	strcat(result, str2);
	return (result);
}
