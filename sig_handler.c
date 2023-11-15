#include "shell.h"
#include <unistd.h>

/**
 * handle_signal - Signal handler for handling ctrl + c during runtime
 *
 * @signal_number: Unused parameter (just for betty)
 */
void handle_signal(int signal_number) {
    (void)signal_number;
    write(1, "\n$ ", 3);
}

/**
 * handle_signal2 - Signal handler for handling ctrl + c during command
 * execution
 *
 * @signal_number: Unused parameter (just for betty)
 */
void handle_signal2(int signal_number) {
    (void)signal_number;
    write(1, "\n", 1);
}
