#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH_SEPARATOR ':'

char *_pathcheck(const char *path) {
    if (!path)
        return (NULL);

    size_t i;
    int count = 0;
    size_t len = strlen(path);

    for (i = 0; i < len; i++) {
        if ((path[i] == '=' && path[i + 1] == PATH_SEPARATOR) ||
            (path[i] == PATH_SEPARATOR &&
             (path[i + 1] == PATH_SEPARATOR || path[i + 1] == '\0'))) {
            count++;
        }
    }

    if (count == 0)
        return (NULL);

    size_t nsize = len + 1 + count;
    char *npath = malloc(nsize);

    if (!npath)
        return (NULL);

    size_t j = 0;
    for (i = 0; i < nsize; i++, j++) {
        if ((path[j] == '=' && path[j + 1] == PATH_SEPARATOR) ||
            (path[j] == PATH_SEPARATOR &&
             (path[j + 1] == PATH_SEPARATOR || path[j + 1] == '\0'))) {
            npath[i] = path[j];
            npath[i + 1] = '.';
            i++;
        } else {
            npath[i] = path[j];
        }
    }

    return (npath);
}

char *_path(const char *cmd, char **env, ShellInfo *shpack) {
    if (!cmd || !env || !shpack)
        return (NULL);

    struct stat st;
    char *path2 = _get_environment_variable("PATH", env);

    if (!path2)
        return (NULL);

    char *path = _str_duplicate(path2);
    char *pathcheck = _pathcheck(path);

    if (pathcheck)
        path = pathcheck;

    char *delim = ":=";
    char *token = _string_token(path, delim);

    while (token) {
        char *concat = concatenate_strings(token, "/");
        char *concat2 = concatenate_strings(concat, cmd);
        free(concat);

        if (stat(concat2, &st) == 0) {
            free(path);
            return (concat2);
        }

        free(concat2);
        token = _string_token(NULL, delim);
    }

    free(path);
    return (NULL);
}
