/**
 * unset_environment_variable - Unsets an environmental variable
 *
 * @env: Array of environment variables
 * @variable: Environment variable to unset
 * @shell_info: Struct with shell info
 *
 * Return: Modified environment array on success, NULL on error
 */
char **unset_environment_variable(char **env, char *variable, ShellInfo *shell_info)
{
    int i, j, check, l, lenv, found;
    char **copy;

    /* Check for null inputs */
    if (!env || !variable)
    {
        handle_error(3, shell_info, 1);
        return NULL;
    }

    /* Get the lengths of the variable and the environment array */
    l = string_length(variable);
    lenv = string_array_length(env);

    /* Search for the variable in the environment array */
    for (i = 0, found = 0; i < lenv; i++)
    {
        for (check = 0, j = 0; j < l && env[i][j] != '\0'; j++)
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

        if (check == l && env[i][check] == '=')
        {
            found = 1;
            break;
        }
    }

    /* If the variable was not found, return an error */
    if (!found)
    {
        write(2, "VARIABLE not found\n", 19);
        return NULL;
    }

    /* Create a copy of the environment array, without the variable to be unset */
    if (lenv > 1)
    {
        copy = copy_double_pointer(env, lenv - 1, i);
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

    /* Free the old environment array and return the new one */
    free_double_pointer(env);
    return copy;
}
