#include "shell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * power - Calculate the power of a number.
 * @base: base number.
 * @exponent: power.
 *
 * Return: Result of base to the power of exponent.
 */
long power(base, exponent)
    long base;
    long exponent;
{
    long result = 1;
    
    for (long i = 0; i < exponent; i++)
    {
        result *= base;
    }

    return (result);
}

/**
 * convert_to_integer - Convert a string to an integer.
 * @s: input string.
 *
 * Return: Transformed integer. On error: (-1) for inappropriate entry.
 */
long convert_to_integer(s)
    char *s;
{
    long result = 0;
    long sign = 1;

    if (!s)
    {
        return (0);
    }

    if (*s == '-')
    {
        sign = -1;
        s++;
    }

    while (*s >= '0' && *s <= '9')
    {
        result = result * 10 + (*s - '0');
        s++;
    }

    return (sign * result);
}
