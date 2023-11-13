#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"

char *_string_token(char *str, const char *delimiter)
{
    static char *step = NULL;
    static int isEnd = 0;

    if (str)
    {
        isEnd = 0;
        step = str;
    }

    if (isEnd)
        return NULL;

    while (*step && strchr(delimiter, *step))
        ++step;

    if (!*step)
    {
        isEnd = 1;
        return NULL;
    }

    char *start = step;

    while (*step && !strchr(delimiter, *step))
        ++step;

    if (*step)
        *step++ = '\0';
    else
        isEnd = 1;

    return start;
}
