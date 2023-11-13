#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"

/**
 * @brief Tokenize a string
 *
 * @param str String to tokenize (if NULL, continue from the previous position)
 * @param delimiter Delimiter characters
 * @return Tokenized substring or NULL if the end of the string is reached
 */
char *_string_token(char *str, const char *delimiter)
{
    static char *step = NULL;  // Static variable to keep track of the position in the string
    static int isEnd = 0;      // Static variable to indicate if the end of the string is reached

    // If str is not NULL, initialize the tokenizer with a new string
    if (str)
    {
        isEnd = 0;
        step = str;
    }

    // If the end is reached, return NULL
    if (isEnd)
        return NULL;

    switch (*step)
    {
    case '\0':
        isEnd = 1;
        return NULL;

    default:
        // Skip leading delimiter characters
        while (*step && _strchr(delimiter, *step))
            ++step;

        // If the end is reached after skipping delimiters, set isEnd and return NULL
        if (!*step)
        {
            isEnd = 1;
            return NULL;
        }

        // Save the start position of the token
        char *start = step;

        // Move step to the end of the token
        while (*step && !_strchr(delimiter, *step))
            ++step;

        // If there are more tokens, replace the delimiter with '\0' and move step to the next character
        if (*step)
            *_strchr(delimiter, *step) = '\0';
        // If there are no more tokens, set isEnd
        else
            isEnd = 1;

        return start;  // Return the token
    }
}
