#include "shell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * main - Main function for the shell program
 *
 * @argc: Count of input parameters to program
 * @argv: Parameters as input to program
 * @env: Unix environment
 *
 * Return: Should only exit through shell inputs
 */
int main(int argc, char **argv, char **env)
{
	size_t buffer_size = 0;
	char **command, *path_command, *input_buffer = NULL;
	ShellInfo *shell_info;
	int error_number = 0, exit_number = 0, logical_relation = 0,
	    is_runnable = 0, size_env, unset_environment = 0;
	ssize_t is_builtin;

	if (argc > 1 || argv == NULL)
	{
		write(2, "Please run with no arguments\n", 29);
		exit(127);
	}

	signal(SIGINT, handle_signal);

	size_env = string_array_length(env);
	env = copy_double_pointer(env, size_env, size_env);
	shell_info = initialize_shell_info(argv[0], &error_number, &exit_number, &logical_relation, &is_runnable, &env, &unset_environment);

	while (1)
	{
		command = NULL;
		command = check_input(argc, argv, &buffer_size, &input_buffer, shell_info);

		if (!command)
		{
			continue;
		}

		add_command(shell_info, input_buffer, command[0], command);
		is_builtin = execute_built_ins(shell_info);

		switch (is_builtin)
		{
		case -1:
		case 1:
			continue;
		default:
			break;
		}

		path_command = _get_absolute_path(command[0], env, shell_info);
		add_path_to_command(shell_info, path_command);

		if (!path_command)
		{
			free_double_pointer(command);
			shell_info->error_count[0] += 1;
			handle_error(0, shell_info, 127);
		}
		else if (access(path_command, X_OK) == -1)
		{
			handle_error(1, shell_info, 126);
		}
		else
		{
			execute_command(path_command, command, env, shell_info);
		}

		free_double_pointer(command);
		free(path_command);
	}

	free_double_pointer(*(shell_info->environment_copy));
	free(shell_info);
	return (0);
}
