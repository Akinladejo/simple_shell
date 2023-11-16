#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * print_help_help - Display help for the help command
 *
 * Return: No Return
 */
void print_help_help(void)
{
    print_string("Shell HSH, version 1.0(1)-release (x86_64-pc-linux-gnu)\n");
    print_string("These shell commands are defined internally.\n");
    print_string("Type `help' to see this list.\n");
    print_string("Type help 'BUILTIN' to find out more about ");
    print_string("the function 'BUILTIN'.\n\n");
    print_string(" exit [n]\n");
    print_string(" env\n");
    print_string(" setenv [VARIABLE] [VALUE]\n");
    print_string(" unsetenv [VARIABLE]\n");
    print_string(" cd [DIRECTORY]\n");
    print_string(" help [BUILTIN ...]\n");
    print_string(" alias [name[='value'] ...]\n");
}
