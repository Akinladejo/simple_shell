#include "shell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * _string_token - Tokenize a string
 *
 * This function tokenizes a string based on the specified delimiter.
 *
 * @str: String to tokenize (if NULL, continue from the previous position)
 * @delimiter: Delimiter characters
 *
 * Return: Tokenized substring or NULL if the end of the string is reached
 */
char *_string_token(char *str, const char *delimiter)
{
    static char *step = NULL;
    static int isEnd = 0;
    char *start;

    if (str)
    {
        isEnd = 0;
        step = str;
    }

    if (isEnd)
        return (NULL);

    char *start = NULL; /* Pointer to the start of the token */

    switch (*step)
    {
        case '\0':
            isEnd = 1;
            return (NULL);

        default:
            while (*step && strchr(delimiter, *step))
            {
                ++step;
            }

            if (!*step)
            {
                isEnd = 1;
                return (NULL);
            }

            start = step;

            while (*step && !strchr(delimiter, *step))
            {
                ++step;
            }

            if (*step)
            {
                *strchr(delimiter, *step) = '\0';
                ++step;
            } else
            {
                isEnd = 1;
            }

            return (start);
    }
}
