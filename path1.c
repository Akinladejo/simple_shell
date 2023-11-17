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
 * Return: The full path of the command if found, or NULL if not found.
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
