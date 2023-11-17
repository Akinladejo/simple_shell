#include "shell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * init_string_token - Initialize the string tokenization process
 * @str: String to tokenize
 *
 * This function initializes the string tokenization process by setting up
 * the static variables and returning a pointer to the start of the string.
 *
 * Return: Pointer to the start of the string
 */
char *init_string_token(char *str)
{
	static char *step;
	static int isEnd;

	if (str)
	{
		isEnd = 0;
		step = str;
	}

	return (step);
}

/**
 * _string_token - Tokenize a string
 * @delimiter: Delimiter characters
 *
 * This function tokenizes a string based on the specified delimiter.
 *
 * Return: Tokenized substring or NULL if the end of the string is reached
 */
char *_string_token(char *str, const char *delimiter);
{
	char *start;
	static char *step;
	static int isEnd;

	if (*step == '\0')
	{
		isEnd = 1;
		return (NULL);
	}

	start = NULL;

	while (*step && strchr(delimiter, *step))
	{
		++step;
	}

	if (!*step)
	{
		isEnd = 1;
		return (NULL);
	}

	start = step;

	while (*step && !strchr(delimiter, *step))
	{
		++step;
	}

	if (*step)
	{
		*strchr(delimiter, *step) = '\0';
		++step;
	}
	else
	{
		isEnd = 1;
	}

	return (start);
}
