#include "shell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * get_parameters - Tokenize the input buffer into parameters
 * @raw_buffer: The raw input buffer
 * @shell_info: Shell information structure
 *
 * Return: Array of pointers to parameters or NULL on failure
 */
char **get_parameters(char *raw_buffer, ShellInfo *shell_info)
{
	char **buffer, *cp_raw_buffer;
	ssize_t cnt = 0, i = 0;

	cp_raw_buffer = _str_duplicate(raw_buffer);
	switch (!cp_raw_buffer)
	{
		case 1:
			handle_error(7, shell_info, 1);
			return (NULL);
	}

	if (_string_token(cp_raw_buffer, " \n"))
		cnt++;
	else
	{
		free(cp_raw_buffer);
		return (NULL);
	}

	while (_string_token(NULL, " \n"))
		cnt++;

	free(cp_raw_buffer);
	buffer = malloc(sizeof(char *) * (cnt + 1));
	switch (!buffer)
	{
		case 1:
			handle_error(7, shell_info, 1);
			return (NULL);
	}

	buffer[0] = _string_token(raw_buffer, " \n");
	for (i = 1; i < cnt && buffer[i - 1]; i++)
		buffer[i] = _string_token(NULL, " \n");

	switch (!buffer[i - 1])
	{
		case 1:
			handle_error(8, shell_info, 1);
			free_double_pointer(buffer);
			return (NULL);
	}

	buffer[i] = NULL;
	return (buffer);
}
