#include "shell.h"
#include <stdlib.h>

/**
 * concatenate_strings - Concatenates two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Pointer to the concatenated string.
 */
char *concatenate_strings(const char *s1, const char *s2)
{
	size_t l1, l2;
	char *result;

	if (s1 == NULL)
	{
		s1 = "";
	}

	if (s2 == NULL)
	{
		s2 = "";
	}

	l1 = string_length(s1);
	l2 = string_length(s2);
	result = malloc(sizeof(char) * (l1 + l2 + 1));

	if (result == NULL)
	{
		return (NULL);
	}

	_string_copy(result, s1);
	/* Copy the second string into the result after the first one */
	_string_copy(result + l1, s2);
	return (result);
}
