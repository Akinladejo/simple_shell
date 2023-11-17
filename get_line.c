#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

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
 * read_file_into_buffer - Reads data from a file descriptor.
 *
 * @buf: Pointer to the buffer
 * @len: Pointer to the length of the buffer
 * @size: Size of the buffer
 * @fd: File descriptor to read from
 * Return: Number of bytes read, or -1 on failure
 */
int read_file_into_buffer(char **buf, size_t *len, size_t size, int fd)
{
	int read_result;

	read_result = read(fd, *buf + *len, size - *len);

	if (read_result == -1)
	{
		return (-1);
	}

	return (read_result);
}

/**
 * resize_buffer - Resizes the buffer if needed.
 *
 * @buf: Pointer to the buffer
 * @size: Pointer to the size of the buffer
 * Return: 1 on success, 0 on failure
 */
int resize_buffer(char **buf, size_t *size)
{
	*size *= 2;

	*buf = _realloc(*buf, *size / 2, *size);
	return ((*buf != NULL) ? 1 : 0);
}

/**
 * process_buffer - Processes the buffer.
 *
 * @buf: Pointer to the buffer
 * @len: Length of the buffer
 * @size: Pointer to the size of the buffer
 * Return: 1 if newline is found, 0 otherwise
 */
int process_buffer(char *buf, size_t len, char **buffer,
			size_t *buffer_size, size_t *size)
{
	size_t i;

	for (i = 0; i < len; i++)
	{
		switch (buf[i])
		{
			case '\n':
				buf[i] = '\0';
				*buffer = buf;
				*buffer_size = *size;
				return (1);
			default:
				break;
		}
	}
	return (0);
}

/**
 * get_line - Reads a line from a file descriptor into a buffer.
 *
 * @buffer: Pointer to the buffer that will contain the line
 * @buffer_size: Pointer to the size of the buffer
 * @fd: File descriptor to read from
 * Return: (Number of bytes read, or -1 on failure)
 */
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int get_line(char **buffer, size_t *buffer_size, int fd)
{
	char *buf = NULL;
	size_t size = BUFFER_SIZE;
	size_t len = 0;
	int read_result;

	buf = malloc(size);
	if (buf == NULL)
		return (-1);

	while (1)
	{
		read_result = read_file_into_buffer(&buf, &len, size, fd);

		if (read_result == -1)
		{
			free(buf);
			return (-1);
		}

		if (read_result == 0)
			break;

		len += read_result;

		if (len >= size && !resize_buffer(&buf, &size))
		{
			free(buf);
			return (-1);
		}

		if (process_buffer(buf, len, buffer, buffer_size, &size))
			return (len);
	}

	free(buf);
	return ((len == 0) ? (size_t)-1 : len);
}
