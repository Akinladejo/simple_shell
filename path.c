#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH_SEPARATOR ':'

/**
 * _pathcheck - Add a dot after each PATH_SEPARATOR in the given path
 * @path: The input path string
 *
 * Return: A newly allocated string with dots added after each PATH_SEPARATOR
 *         or NULL if the input is NULL or no PATH_SEPARATOR is found.
 */
char *_pathcheck(const char *path)
{
	size_t len;
	size_t j;
	size_t i;
	size_t nsize;
	char *npath;

	if (!path)
		return (NULL);

	len = strlen(path);
	nsize = len + 1; /* Move declaration here */
	npath = malloc(nsize);

	if (!npath)
		return (NULL);

	j = 0;
	for (i = 0; i < nsize; i++, j++)
	{
		if ((path[j] == '=' && path[j + 1] == PATH_SEPARATOR) ||
			(path[j] == PATH_SEPARATOR &&
			(path[j + 1] == PATH_SEPARATOR || path[j + 1] == '\0')))
		{
			npath[i] = path[j];
			npath[i + 1] = '.';
			i++;
		}
		else
		{
			npath[i] = path[j];
		}
	}

	return (npath);
}

/**
 * _path - Search for the given command in the PATH environment variable
 * @cmd: The command to search for
 * @env: The environment variables
 * @shpack: The ShellInfo structure
 *
 * : The full path of the command if found, or NULL if not found.
 */
char *_path(const char *cmd, char **env, ShellInfo *shpack)
{
	struct stat st;
	char *path2;
	char *pathcheck;
	char *delim;
	char *token;
	char *path;

	if (!cmd || !env || !shpack)
		return (NULL);
	path2 = _get_environment_variable("PATH", env);
	if (!path2)
		return (NULL);

	path = _str_duplicate(path2);
	pathcheck = _pathcheck(path);
	if (pathcheck)
		path = pathcheck;
	delim = ":=";
	token = _string_token(path, delim);
	while (token)
	{
		char *concat = concatenate_strings(token, "/");
		char *concat2 = concatenate_strings(concat, cmd);
		free(concat);
		if (stat(concat2, &st) == 0)
		{
			free(path);
			return (concat2);
		}
		free(concat2);
		token = _string_token(NULL, delim);
	}
	free(path);
	return (NULL);
}

/* Add your Betty-style comments for the missing functions here */

/**
 * _get_environment_variable - Get the value of an environment variable
 * @name: The name of the environment variable
 * @env: The environment variables
 *
 * Return: The value of the environment variable if found, or NULL if not found.
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
			return env[i] + strlen(name) + 1;
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
