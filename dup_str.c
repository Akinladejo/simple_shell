#include <stdlib.h>
#include "shell.h"

/**
 * _str_duplicate - Duplicate a string
 * @str: Source string to duplicate
 *
 * Return: Pointer to the duplicated string
 * On error: NULL for inappropriate entry or memory allocation failure
 */
char *_str_duplicate(char *str)
{
    char *duplicate;

    if (!str)
        return NULL;

    duplicate = malloc((_strlen(str) * sizeof(*duplicate)) + 1);

    if (!duplicate)
        return NULL;

    _strcpy(duplicate, str);

    return duplicate;
}

/**
 * string_length - Get the length of a string
 * @s: Input string
 *
 * Return: Length of the string
 * On error: -1 for inappropriate entry
 */
int string_length(char *s)
{
    return ((!*s) ? 0 : 1 + string_length(s + 1));
}

/**
 * _strcpy - Copy a source string to a destination string
 * @dest: Destination where the string will be stored
 * @src: Source string to copy from
 *
 * Return: Pointer to the destination string
 * On error: NULL for inappropriate entry
 */
char *_strcpy(char *dest, char *src)
{
    int i = 0;

    for (i = 0; *(src + i) != '\0'; i++)
        *(dest + i) = *(src + i);

    *(dest + i) = *(src + i); /* Adding '\0' character */

    return dest;
}
