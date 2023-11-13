/**
 * @brief Unsets an environmental variable
 *
 * @param env Array of environment variables
 * @param variable Environment variable to unset
 * @param shell_info Struct with shell info
 *
 * @return Modified environment array on success, NULL on error
 */
char **unset_environment_variable(char **env, const char *variable, ShellInfo *shell_info)
{
    // Check for null inputs
    if (!env || !variable)
    {
        handle_error(3, shell_info, 1);
        return NULL;
    }

    // Get the lengths of the variable and the environment array
    size_t var_length = string_length(variable);
    size_t env_length = string_array_length(env);

    // Search for the variable in the environment array
    size_t i, j;
    int found = 0;

    for (i = 0; i < env_length; i++)
    {
        int check = 0;

        for (j = 0; j < var_length && env[i][j] != '\0'; j++)
        {
            if (variable[j] == '=')
            {
                handle_error(3, shell_info, 2);
                return NULL;
            }

            if (env[i][j] == variable[j])
            {
                check++;
            }
        }

        if (check == var_length && env[i][check] == '=')
        {
            found = 1;
            break;
        }
    }

    // Use a switch statement to handle different cases
    switch (found)
    {
    case 0:
        // If the variable was not found, return an error
        write(2, "VARIABLE not found\n", 19);
        return NULL;

    case 1:
        // Create a copy of the environment array, without the variable to be unset
        char **copy = NULL;

        if (env_length > 1)
        {
            copy = copy_double_pointer(env, env_length - 1, i);

            if (!copy)
            {
                handle_error(7, shell_info, 1);
                return NULL;
            }
        }
        else
        {
            copy = NULL;
            shell_info->unset_environment[0] = 1;
        }

        // Free the old environment array and return the new one
        free_double_pointer(env);
        return copy;

    default:
        // Should not reach here, but handle it just in case
        handle_error(8, shell_info, 1);
        return NULL;
    }
}
