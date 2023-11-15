#include "shell.h"
#include <stdlib.h>

/**
 * concatenate_strings - Concatenates two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Pointer to the concatenated string.
 */
char *concatenate_strings(char *s1, char *s2)
{
	if (s1 == NULL)
	{
		s1 = "";
	}

	if (s2 == NULL)
	{
		s2 = "";
	}

	size_t l1 = string_length(s1);
	size_t l2 = string_length(s2);

	char *result = malloc(sizeof(char) * (l1 + l2 + 1));

	if (result == NULL)
	{
		return (NULL);
	}

	_string_copy(result, s1);

	_string_copy(result + l1, s2);

	return (result);
}
