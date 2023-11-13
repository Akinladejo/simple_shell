#include <unistd.h>
#include "shell.h"

/**
 * @brief Get the value of an environment variable
 *
 * @param name Name of the environment variable
 * @param env Array of environment variables
 * @return Value of the environment variable or NULL if not found
 */
char *_get_environment_variable(const char *name, char **env) {
    if (!env || !name)
        return NULL;

    // Calculate the length of the name
    size_t name_length = 0;
    while (name[name_length] != '\0')
        name_length++;

    // Search for the variable in the environment array
    for (int i = 0; env[i] != NULL; i++) {
        size_t check = 0;
        size_t j = 0;

        // Check each character of the name in the current environment variable
        while (j < name_length && env[i][j] != '\0') {
            if (env[i][j] == name[j])
                check++;
            j++;
        }

        // If the name is found and followed by '=', return the environment variable
        if (check == name_length && env[i][check] == '=')
            return env[i];
    }

    return NULL;  // Variable not found
}
