#include "shell.h"
#include <stdlib.h>

/**
 * _str_duplicate - Duplicate a string
 * @str: Source string to duplicate
 *
 * Return: Pointer to the duplicated string
 * On error: NULL for inappropriate entry or memory allocation failure
 */
char *_str_duplicate(char *str)
{
	char *duplicate;

	if (!str)
		return (NULL);

	duplicate = malloc((string_length(str) * sizeof(*duplicate)) + 1);

	if (!duplicate)
		return (NULL);

	_string_copy(duplicate, str);

	return (duplicate);
}

/**
 * string_length - Get the length of a string
 * @s: Input string
 *
 * Return: Length of the string
 * On error: -1 for inappropriate entry
 */
int string_length(const char *s)
{
	return (!*s) ? 0 : 1 + string_length(s + 1);
}

/**
 * _string_copy - Copy a source string to a destination string
 * @destination: Destination where the string will be stored
 * @source: Source string to copy from
 *
 * Return: Pointer to the destination string
 * On error: NULL for inappropriate entry
 */
char *_string_copy(char *destination, const char *source)
{
	int i = 0;

	for (i = 0; *(source + i) != '\0'; i++)
		*(destination + i) = *(source + i);

	*(destination + i) = *(source + i); /* Adding '\0' character */

	return (destination);
}
