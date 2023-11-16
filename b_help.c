#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * display_help_unsetenv - Display help for unsetenv built-in command.
 *
 * Return: No Return
 */
void display_help_unsetenv(void)
{
	print_string("unsetenv: unsetenv [VARIABLE]\n");
	print_string("    Initializes a new environment variable, or ");
	print_string("    modifies an existing one.\n\n");
	print_string("    VARIABLE must not have the character '='.\n");
	print_string("    If no arguments are given, setenv prints the current ");
	print_string("    environment.\n");
}

/**
 * display_help_change_directory - Display help for cd built-in command.
 *
 * Return: No Return
 */

void display_help_change_directory(void)
{
	print_string("cd: cd [DIRECTORY]\n");
	print_string("    Change the shell working directory.\n\n");
	print_string("    Change the current directory to DIR.  ");
	print_string("    The default DIR is the value of the\n");
	print_string("    HOME shell variable.\n\n");
	print_string("    Options:\n");
	print_string("    -  If a minus signed is used instead a directory, ");
	print_string("    cd will change to the\n");
	print_string("       previous used directory\n\n");
	print_string("    Each time cd runs successfully, the env variable ");
	print_string("    PWD is updated\n\n");
	print_string("    Exit Status:\n");
	print_string("    Returns 1 if the directory is changed, and if $PWD is set ");
	print_string("    successfully when\n");
	print_string("    is used; -1 otherwise.\n");
}

/**
 * display_help_help - Display help for help built-in command.
 *
 * Return: No Return
 */

void display_help_help(void)
{
	print_string("help: help [BUILTIN ...]\n");
	print_string("    Display information about builtin commands.\n\n");
	print_string("    Displays brief summaries of builtin commands.  If "
		"BUILTIN is\n");
	print_string("    specified, gives detailed help on all commands ");
	print_string("    matching BUILTIN,\n");
	print_string("    otherwise, the list of help topics is printed.\n\n");
	print_string("    Arguments:\n");
	print_string("      BUILTIN   Builtin specifying a help topic\n\n");
	print_string("    Exit Status:\n");
	print_string("    Returns success unless PATTERN is not found or an invalid ");
	print_string("    option is given.\n");
}

/**
 * display_help_alias - Display help for alias built-in command.
 *
 * Return: No Return
 */

void display_help_alias(void)
{
	print_string("alias: alias alias [name[='value'] ...]\n");
	print_string("    Define or display aliases.\n\n");
	print_string("    Without arguments, `alias' prints the list of aliases ");
	print_string("    in the reusable\n");
	print_string("    form `alias NAME=VALUE' on standard output.\n\n");
	print_string("     Otherwise, an alias is defined for each NAME whose ");
	print_string("    VALUE is given.\n");
	print_string("    A trailing space in VALUE causes the next word to ");
	print_string("    be checked for\n");
	print_string("    alias substitution when the alias is expanded.\n\n");
	print_string("    Exit Status:\n");
	print_string("    alias returns true unless a NAME is supplied for which ");
	print_string("    no alias has been\n");
	print_string("    defined.\n");
}
