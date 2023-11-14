#include "shell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Get parameters from the input buffer
 *
 * This function tokenizes the raw input buffer and returns an array of strings
 * representing the parameters of a command.
 *
 * @param raw_buffer Raw input buffer containing the command and its parameters.
 * @param shell_info Pointer to the ShellInfo structure.
 * @return On success, returns an array of strings representing the parameters.
 *         On failure, returns NULL.
 */
char **get_parameters(char *raw_buffer, ShellInfo *shell_info) {
	char **buffer, *cp_raw_buffer;
	ssize_t cnt = 0, i = 0;

	// Duplicate the raw_buffer to avoid modifying the original string
	cp_raw_buffer = _str_duplicate(raw_buffer);
	switch (!cp_raw_buffer) {
	case 1:
		handle_error(7, shell_info, 1);
		return NULL;
	}

	// Count the number of parameters
	if (_string_token(cp_raw_buffer, " \n"))
		cnt++;
	else {
		free(cp_raw_buffer);
		return NULL;
	}
	while (_string_token(NULL, " \n"))
		cnt++;

	// Free the duplicated raw_buffer
	free(cp_raw_buffer);

	// Allocate memory for the buffer
	buffer = malloc(sizeof(char *) * (cnt + 1));
	switch (!buffer) {
	case 1:
		handle_error(7, shell_info, 1);
		return NULL;
	}

	// Tokenize the raw_buffer and store the parameters in the buffer array
	buffer[0] = _string_token(raw_buffer, " \n");
	for (i = 1; i < cnt && buffer[i - 1]; i++)
		buffer[i] = _string_token(NULL, " \n");

	// Check for incomplete tokens
	switch (!buffer[i - 1]) {
	case 1:
		handle_error(8, shell_info,
			     1); // Adjust the error code as needed
		free_double_pointer(buffer);
		return NULL;
	}

	// Null-terminate the buffer
	buffer[i] = NULL;

	return buffer;
}
