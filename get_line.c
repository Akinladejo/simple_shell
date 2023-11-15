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
 * Return: Pointer to the memory area dest
 */
char *_memset(char *dest, char value, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		dest[i] = value;
	}
	return (dest);
}

/**
 * _realloc - Reallocates a memory block using malloc and free
 *
 * @ptr: Pointer to the old memory block
 * @old_size: Size of the old memory block
 * @new_size: Size of the new memory block
 * Return: (Pointer to the newly allocated memory block)
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}

	if (ptr != NULL && old_size > 0)
	{
		memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}

	return (new_ptr);
}

/**
 * get_line - Reads a line from a file descriptor into a buffer
 *
 * @buffer: Pointer to the buffer that will contain the line
 * @buffer_size: Pointer to the size of the buffer
 * @file_descriptor: File descriptor to read from
 * Return: (Number of bytes read, or -1 on failure)
 */
int get_line(char **buffer, size_t *buffer_size, int file_descriptor)
{
	char *buf = NULL;
	size_t size = BUFFER_SIZE;
	size_t len = 0;
	int read_result;

	buf = malloc(size);
	if (buf == NULL)
	{
		return (-1);
	}

	while (1)
	{
		read_result = read(file_descriptor, buf + len, size - len);
		if (read_result == -1)
		{
			free(buf);
			return (-1);
		}

		if (read_result == 0)
		{
			break;
		}

		len += read_result;

		if (len >= size)
		{
			size *= 2;
			buf = _realloc(buf, size, size);
			if (buf == NULL)
			{
				free(buf);
				return (-1);
			}
		}

		for (size_t i = 0; i < len; i++)
		{
			switch (buf[i])
			{
			case '\n':
				buf[i] = '\0';
				*buffer = buf;
				*buffer_size = size;
				return (len);

			default:
				break;
			}
		}
	}

	if (len == 0)
	{
		free(buf);
		return (-1);
	}

	buf[len] = '\0';
	*buffer = buf;
	*buffer_size = size;
	return (len);
}
