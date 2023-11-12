#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * @brief Reverses a string in place
 *
 * @param s String to reverse
 */
void reverse_string(char *s)
{
    int length = 0;
    while (s[length] != '\0')
    {
        length++;
    }

    int i = 0, j = length - 1;
    while (i < j)
    {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++, j--;
    }
}

/**
 * @brief Calculates the length of a number in a given base
 *
 * @param n Number
 * @param base Base of the number
 * @return Length of the number
 */
int number_length(unsigned long int n, unsigned long int base)
{
    int length = 0;

    while (n > 0)
    {
        n = n / base;
        length++;
    }

    return length;
}

/**
 * @brief Converts an integer to a string
 *
 * @param n Number
 * @return Pointer to the string
 */
char *_itoa(int n)
{
    unsigned long int base = 10;
    unsigned long int value = (n < 0) ? -n : n;
    int length = (n == 0) ? 1 : number_length(value, base) + 1;

    char *str = malloc(length);
    if (!str)
    {
        write(2, "Memory Error", 22);
        return NULL;
    }

    int i = 0;
    while (value > 0)
    {
        str[i++] = (value % base) + '0';
        value = value / base;
    }

    if (n < 0)
    {
        str[i++] = '-';
    }

    str[i] = '\0';
    reverse_string(str);
    return str;
}

/**
 * @brief Generates additional error information
 *
 * @param errn Number corresponding to the type of error
 * @param result Error part from _error
 * @param option Command option
 * @return Pointer to the string
 */
char *generate_error_info(int errn, char *result, char *option);

/**
 * @brief Creates a string with an error line
 *
 * @param errn Number corresponding to the type of error
 * @param shell_info Struct containing shell information
 * @param exit_num Value of exit the shell should have
 * @return 0 success, -1 fail
 */
int create_error(int errn, ShellInfo *shell_info, int exit_num)
{
    int error_count = shell_info->error_count[0];
    char *current_command = shell_info->current_command;
    char **command_options = shell_info->command_options;
    char *shell_name = shell_info->shell_name;
    char *error_messages[] = {
        "not found", "Permission denied", "Illegal number",
        "name is NULL, points to a string of len 0, or has an '=' char.",
        "can't cd to ", "Illegal option ", "Help command error",
        "Error allocating memory", "Wrong Alias",
        NULL};

    char *result = concatenate_strings(shell_name, ": ");
    if (!result)
    {
        return (write(2, "Memory Error", 22), -1);
    }

    char *temp_result = concatenate_strings(result, _itoa(error_count));
    free(result);

    if (!temp_result)
    {
        return (write(2, "Memory Error", 22), -1);
    }

    result = concatenate_strings(temp_result, ": ");
    free(temp_result);

    temp_result = concatenate_strings(result, current_command);
    free(result);

    result = concatenate_strings(temp_result, ": ");
    free(temp_result);

    temp_result = concatenate_strings(result, error_messages[errn]);
    free(result);

    if (errn > 1 && errn < 6 && errn != 3)
    {
        temp_result = generate_error_info(errn, temp_result, command_options[1]);
    }

    if (!temp_result)
    {
        write(2, "Memory Error", 22);
        return -1;
    }

    int length = 0;
    while (temp_result[length] != '\0')
    {
        length++;
    }

    write(2, temp_result, length);
    write(2, "\n", 1);

    free(temp_result);
    shell_info->exit_number[0] = exit_num;
    return 0;
}

/**
 * @brief Generates additional modes for error information
 *
 * @param errn Number corresponding to the type of error
 * @param result Error part from _error
 * @param option Command option
 * @return Pointer to the string
 */
char *generate_error_info(int errn, char *result, char *option)
{
    char *temp_result = NULL;
    char *colspace = ": ";

    if (errn == 2)
    {
        temp_result = concatenate_strings(result, colspace);
        if (!temp_result)
        {
            write(2, "Memory Error", 22);
            return NULL;
        }

        char *temp = concatenate_strings(temp_result, option);
        free(temp_result);
        temp_result = temp;
        if (!temp_result)
        {
            write(2, "Memory Error", 22);
            return NULL;
        }
    }

    if (errn > 3)
    {
        char *temp = concatenate_strings(temp_result, option);
        free(temp_result);
        temp_result = temp;
        if (!temp_result)
        {
            write(2, "Memory Error", 22);
            return NULL;
        }
    }

    return temp_result;
}
