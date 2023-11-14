#include "shell.h"
#include <stdlib.h>

/**
 * concatenate_strings - concatenates two strings
 * @s1: string1
 * @s2: string2
 *
 * Return: Pointer to the concatenated string
 */
char *concatenate_strings(char *s1, char *s2) {
	if (s1 == NULL) {
		s1 = ""; // Use empty string if s1 is NULL
	}

	if (s2 == NULL) {
		s2 = ""; // Use empty string if s2 is NULL
	}

	// Calculate lengths of the strings
	size_t l1 = string_length(s1);
	size_t l2 = string_length(s2);

	// Allocate memory for the concatenated string
	char *result = malloc(sizeof(char) * (l1 + l2 + 1));

	if (result == NULL) {
		return NULL; // Return NULL on malloc failure
	}

	// Copy the first string to the result
	_string_copy(result, s1);

	// Concatenate the second string to the result
	_string_copy(result + l1, s2);

	return result;
}
