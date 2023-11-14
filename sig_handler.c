#include "shell.h"
#include <unistd.h>

/**
 * @brief Signal handler for handling ctrl + c during runtime
 *
 * @param signal_number Unused parameter (just for betty)
 */
void handle_signal(int signal_number) {
	(void)signal_number;
	write(1, "\n$ ", 3);
}

/**
 * @brief Signal handler for handling ctrl + c during command execution
 *
 * @param signal_number Unused parameter (just for betty)
 */
void handle_signal2(int signal_number) {
	(void)signal_number;
	write(1, "\n", 1);
}
