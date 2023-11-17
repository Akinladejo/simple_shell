#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * _memset - Fills the first n bytes of the memory area pointed to by dest
 *           with the constant byte value.
 *
 * @dest: Pointer to the memory area
 * @value: Byte value to be set
 * @count: Number of bytes to set
 * Return: (Pointer to the memory area dest)
 */
char *_memset(char *dest, char value, unsigned int count)
{
	unsigned  int i;

	for (i = 0; i < count; i++)
	{
		dest[i] = value;
	}
	return (dest);
}
