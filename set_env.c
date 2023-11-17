#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * free_double_pointer - Frees a double pointer.
 * @pointer: The double pointer to be freed.
 *
 * This function frees the memory occupied by a double pointer.
 * Return: None
 */
void free_double_pointer(char **pointer)
{
	int i; /* Move declaration to the beginning */

	if (!pointer)
		return;

	for (i = 0; pointer[i] != NULL; i++)
		free(pointer[i]);
	free(pointer);
}

/**
 * copy_double_pointer - Copies a double pointer to a new size.
 * @pointer: The original double pointer.
 * @old_size: The old size of the double pointer.
 * @new_size: The new size of the double pointer.
 *
 * This function copies a double pointer to a new size.
 * Returns the copied double pointer or NULL on failure.
 */
char **copy_double_pointer(char **pointer, int old_size, int new_size)
{
	int i; /* Move declaration to the beginning */
	int copy_size
	char **copy
	copy_size = (new_size < old_size) ? new_size : old_size;
	copy = malloc(sizeof(char *) * (copy_size + 1));

	if (!copy)
		return NULL;

	for (i = 0; i < copy_size; i++)
	{
		copy[i] = _str_duplicate(pointer[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return NULL;
		}
	}

	copy[new_size] = NULL;
	return copy;
}

/**
 * string_array_length - Calculates the length of a string array.
 * @array: The string array.
 *
 * This function calculates the length of a string array.
 * Return: The length of the string array.
 */
int string_array_length(char **array)
{
	int length; /* Move declaration to the beginning */

	if (array == NULL)
		return 0;

	for (length = 0; array[length] != NULL; length++)
		;

	return length;
}
