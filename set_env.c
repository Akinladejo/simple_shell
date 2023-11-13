#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * Frees memory associated with a double pointer array of strings.
 *
 * @param pointer: Double pointer to free.
 */
void free_double_pointer(char **pointer) {
    if (!pointer)
        return;

    for (int i = 0; pointer[i] != NULL; i++)
        free(pointer[i]);

    free(pointer);
}

/**
 * Copies a double pointer array of strings with resizing.
 *
 * @param pointer: Double pointer to copy.
 * @param old_size: Original size of the double pointer.
 * @param new_size: New size of the double pointer.
 *
 * @return Pointer to the newly copied double pointer.
 */
char **copy_double_pointer(char **pointer, int old_size, int new_size) {
    if (!pointer && (old_size == new_size))
        return NULL;

    int copy_size = (new_size < old_size) ? new_size : old_size;
    char **copy = malloc(sizeof(char *) * (copy_size + 1));

    if (!copy)
        return NULL;

    if (pointer) {
        for (int i = 0; i < copy_size; i++) {
            copy[i] = _str_duplicate(pointer[i]);

            if (!copy[i]) {
                while (--i >= 0)
                    free(copy[i]);

                free(copy);
                return NULL;
            }
        }
    }

    // Add Null in the end
    copy[new_size] = NULL;

    return copy;
}

/**
 * Calculates the length of a double pointer array (ending in NULL).
 *
 * @param array: Double pointer array.
 *
 * @return Length of the double pointer array.
 */
int string_array_length(char **array) {
    if (!array)
        return 0;

    int length;
    for (length = 0; array[length] != NULL; length++)
        ;

    return length;
}

/**
 * Sets or overwrites an environment variable in the given array.
 *
 * @param env: Array of environment variables.
 * @param variable: Environment variable to set.
 * @param value: Value to set.
 * @param shell_info: Structure with shell information.
 *
 * @return Pointer to the modified environment variable array.
 */
char **set_environment_variable(char **env, char *variable, char *value, ShellInfo *shell_info) {
    if (!variable || string_length(variable) == 0)
        return handle_error(3, shell_info, 1), NULL;

    char *env_join2 = concatenate_strings(variable, "=");
    if (!env_join2)
        return handle_error(3, shell_info, 1), NULL;

    char *env_join = concatenate_strings(env_join2, value);
    free(env_join2);

    if (!env_join)
        return handle_error(3, shell_info, 1), NULL;

    int len_variable = string_length(variable);
    int len_env = string_array_length(env);

    for (int i = 0; env && env[i] != NULL; i++) {
        int check = 0;
        for (int j = 0; j < len_variable && env[i][j] != NULL; j++) {
            if (variable[j] == '=')
                return free(env_join), handle_error(3, shell_info, 2), NULL;

            if (env[i][j] == variable[j])
                check++;
        }

        if (check == len_variable && env[i][check] == '=') {
            free(env[i]);
            char *copy_dup = _str_duplicate(env_join);
            free(env_join);

            if (!copy_dup)
                return handle_error(3, shell_info, 1), NULL;

            return env[i] = copy_dup, env;
        }
    }

    char **copy = copy_double_pointer(env, len_env, len_env + 1);
    free_double_pointer(env);

    if (!copy)
        return free(env_join), handle_error(3, shell_info, 1), NULL;

    env = copy;
    char *copy_dup = _str_duplicate(env_join);
    free(env_join);

    if (!copy_dup)
        return handle_error(3, shell_info, 1), NULL;

    return env[len_env] = copy_dup, env;
}
