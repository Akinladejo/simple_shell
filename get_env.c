#include <unistd.h>
#include "shell.h"

char *_get_environment_variable(const char *name, char **env) {
    if (!env || !name)
        return NULL;

    size_t name_length = 0;
    while (name[name_length] != '\0')
        name_length++;

    for (int i = 0; env[i] != NULL; i++) {
        size_t check = 0;
        size_t j = 0;

        while (j < name_length && env[i][j] != '\0') {
            if (env[i][j] == name[j])
                check++;
            j++;
        }

        if (check == name_length && env[i][check] == '=')
            return env[i];
    }

    return NULL;
}