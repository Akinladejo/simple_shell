#include "shell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * power - Calculate the power of a number
 * @base: base number
 * @exponent: power
 *
 * Return: Result of base to the power of exponent
 */
long power(long base, long exponent)
{
	long result = 1;

	for (long i = 0; i < exponent; i++)
	{
		result *= base;
	}

	return (result);
}

/**
 * convert_to_integer - Convert a string to an integer
 * @s: input string
 *
 * Return: Transformed integer
 *         On error: -1 for inappropriate entry
 */
long convert_to_integer(char *s)
{
	if (!s)
	{
		return (0);
	}

	long result = 0;
	long sign = 1; /* 1 represents positive, -1 represents negative */

	/* Handle the sign */
	if (*s == '-')
	{
		sign = -1;
		s++;
	}

	/* Process digits */
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + (*s - '0');
		s++;
	}

	return (sign * result);
}

/**
 * compare_strings - Compare two strings
 * @string1: first string
 * @string2: second string
 *
 * Return: 0 if strings are equal, another value if not
 */
int compare_strings(char *string1, char *string2)
{
	while (*string1 && *string1 == *string2)
	{
		string1++;
		string2++;
	}

	return ((*string1 - *string2));
}

/**
 * is_digit - Check if a character is a digit
 * @character: character to check
 *
 * Return: 1 if digit, 0 if not
 */
int is_digit(int character)
{
	return ((character >= '0' && character <= '9'));
}

/**
 * is_number - Check if a string is a number
 * @string: input string
 *
 * Return: 1 if the string has only numbers, 0 if not
 */
int is_number(char *string)
{
	while (*string)
	{
		if (!is_digit(*string))
		{
			return (0);
		}
		string++;
	}

	return (1);
}
