#include "shell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @execute_command - Execute a command using fork and execve
 *
 * @program: Path to the command executable
 * @command: Arguments for the command
 * @env: Current environment variables
 * @shell_info: Shell information structure
 *
 * Returns: 0 on success, -1 on error
 */
int execute_command(char *program, char *command[], char **env,
		    ShellInfo *shell_info)
{
	pid_t process, status;
	int execve_status = 0, wait_status = 0;

	process = fork();
	signal(SIGINT, handle_signal2);
	switch (process)
	{
		case -1:
			perror("Fork Error");
			exit(EXIT_FAILURE);
		case 0:
			execve_status = execve(program, command, env);
			if (execve_status == -1)
			{
				_exit(EXIT_FAILURE);
			}
			break;
		default:

			wait_status = wait(&status);
			signal(SIGINT, handle_signal);

			if (wait_status == -1)
			{
				exit(EXIT_FAILURE);
			}

			if (WEXITSTATUS(status) == 0)
			{
				shell_info->exit_number[0] = 0;
			}
			else
			{
				shell_info->exit_number[0] = 2;
			}
	}

	shell_info->error_count[0] += 1;
	return (0);
}
