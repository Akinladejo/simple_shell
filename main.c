/*
 * File: shell.c
 * Author: Akinladejo Andrew and Osei Kofi
 */

#include "shell.h"

void signalHandler(int sig);
int executeCommand(char **args, char **front);

/**
 * signalHandler - Handles signals and prints a new prompt.
 * @sig: The signal number.
 */
void signalHandler(int sig)
{
	char *newPrompt = "\n$ ";
	
	(void)sig;
	signal(SIGINT, signalHandler);
	write(STDIN_FILENO, newPrompt, 3);
}

/**
 * executeCommand - Execute a command in a child process.
 * @args: An array of command arguments.
 * @front: A pointer to the beginning of the args array.
 *
 * Return: If an error occurs - a corresponding error code.
 *         Otherwise - The exit value of the last executed command.
 */
int executeCommand(char **args, char **front)
{
	pid_t childPid;
	int status, flag = 0, ret = 0;
	char *command = args[0];
	
	if (command[0] != '/' && command[0] != '.')
    {
		flag = 1;
		command = getCommandLocation(command);
	}
	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (createError(args, 126));
		else
			ret = (createError(args, 127));
	}
	else
	{
		childPid = fork();
		if (childPid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (childPid == 0)
		{
			execve(command, args, environment);
			if (errno == EACCES)
				ret = (createError(args, 126));
			freeEnvironment();
			freeArguments(args, front);
			freeAliasList(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}

/**
 * main - Entry point for a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *executionResult = &retn;
	char *prompt = "$ ", *newLine = "\n";
	
	programName = argv[0];
	history = 1;
	aliases = NULL;
	signal(SIGINT, signalHandler);
	
	*executionResult = 0;
	environment = copyEnvironment();
	if (!environment)
		exit(-100);
	
	if (argc != 1)
	{
		ret = processFileCommands(argv[1], executionResult);
		freeEnvironment();
		freeAliasList(aliases);
		return (*executionResult);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handleArguments(executionResult);
		freeEnvironment();
		freeAliasList(aliases);
		return (*executionResult);
	}
	
	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handleArguments(executionResult);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, newLine, 1);
			freeEnvironment();
			freeAliasList(aliases);
			exit(*executionResult);
		}
	}
	
	freeEnvironment();
	freeAliasList(aliases);
	return (*executionResult);
}
