/**
 * cd_command - Change the current directory based on the provided arguments.
 * @shell_info: Pointer to the ShellInfo struct containing shell information.
 *
 * Return: On success, returns the exit code (1). On failure, returns -1.
 */
ssize_t cd_command(ShellInfo *shell_info)
{
	char *current_directory = NULL, *directory = NULL, **new_environment,
		*oldpwd = NULL;
	int exit_code = 1;

	if (!check_num_args(shell_info))
	{
		return (-1);
	}

	current_directory = get_current_directory();
	if (!current_directory)
	{
		return (-1);
	}

	directory = get_directory(shell_info);
	if (!directory)
	{
		free(current_directory);
		return (-1);
	}

	change_directory(directory);
	update_environment_variables(directory);

	free(shell_info->command_options);
	free(current_directory);
	free(oldpwd);
	free(directory);

	return (exit_code);
}

/**
 * check_num_args - Check the number of arguments for the cd command.
 * @shell_info: Pointer to the ShellInfo struct containing shell information.
 *
 * Return: 1 if the number of arguments is valid, 0 otherwise.
 */
int check_num_args(ShellInfo *shell_info)
{
	if (shell_info->command_options[1] && !shell_info->command_options[2])
	{
		return (1);
	} else {
		write(2, "cd: too many arguments\n", 23);
		*(shell_info->exit_number) = 2;
		free(shell_info->command_options);
		return (0);
	}
}

/**
 * get_current_directory - Get the current working directory.
 *
 * Return: On success, returns a pointer to the current directory string.
 * On failure, returns NULL.
 */
char *get_current_directory(void)
{
	char *current_directory = getcwd(NULL, 4096);
	if (!current_directory)
	{
		handle_error(4, shell_info, 2);
		return (NULL);
	}

	return (current_directory);
}

/**
 * get_directory - Get the directory argument from the command options.
 * @shell_info: Pointer to the ShellInfo struct containing shell information.
 *
 * Return: Pointer to the directory string.
 */
char *get_directory(ShellInfo *shell_info)
{
	char *directory = NULL;

	if (shell_info->command_options[1])
	{
		directory = shell_info->command_options[1];
	}

	return (directory);
}

/**
 * change_directory - Change the current working directory.
 * @directory: Pointer to the directory string.
 */
void change_directory(char *directory)
{
	int check = chdir(directory);
	if (check != 0)
	{
		handle_error(4, shell_info, 2);
	}
}

/**
 * update_environment_variables - Update environment variables (PWD and OLDPWD).
 * @directory: Pointer to the new working directory.
 */
void update_environment_variables(char *directory)
{
	char **new_environment;

	new_environment = set_environment_variable(*(shell_info->environment_copy), "PWD", directory, shell_info);
	*(shell_info->environment_copy) = new_environment;
	new_environment = set_environment_variable(*(shell_info->environment_copy), "OLDPWD", current_directory, shell_info);
	*(shell_info->environment_copy) = new_environment;
}
