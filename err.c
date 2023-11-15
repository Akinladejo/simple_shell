#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * reverse_string - Reverses a string in place
 *
 * @s: String to reverse
 * Return: Reversed string
 */
void reverse_string(char *s)
{
    int length = 0;
    int i, j;  /* Move declarations to the beginning */

    while (s[length] != '\0') 
    {
        length++;
    }

    i = 0, j = length - 1;
    while (i < j) 
    {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++, j--;
    }
}

/**
 * number_length - Calculates the length of a number in a given base
 *
 * @n: Number
 * @base: Base of the number
 * Return: Length of the number
 */
int number_length(unsigned long int n, unsigned long int base);

/**
 * _itoa - Converts an integer to a string
 *
 * @n: Number
 * Return: Pointer to the string
 */
char *_itoa(int n)
{
    unsigned long int base = 10;
    unsigned long int value = (n < 0) ? -n : n;
    int length = (n == 0) ? 1 : number_length(value, base) + 1;
    int i = 0;  /* Move declaration to the beginning */

    char *str = malloc(length + 1);  /* +1 for the null terminator */
    if (!str) 
    {
        /* handle error differently or change the return type */
        return (NULL);
    }

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
    return (str);
}

/**
 * generate_error_info - Generates additional error information
 *
 * @errn: Number corresponding to the type of error
 * @result: Error part from _error
 * @option: Command option
 * Return: Pointer to the string
 */
char *generate_error_info(int errn, char *result, char *option)
{
    char *temp_result = NULL;
    char *colspace = ": ";
    char *temp;

    switch (errn) 
    {
        case 2:
        {
            temp_result = concatenate_strings(result, colspace);
            if (!temp_result) 
            {
                /* handle error or return NULL */
                return (NULL);
            }
            temp= concatenate_strings(temp_result, option);
            free(temp_result);
            temp_result = temp;
            if (!temp_result) 
            {
                /* handle error or return NULL */
                return (NULL);
            }
        }
        break;

        default:
            if (errn > 3) 
            {
                {
                    char *temp = concatenate_strings(result, colspace);
                    if (!temp) 
                    {
                        /* handle error or return NULL */
                        return (NULL);
                    }

                    temp_result = concatenate_strings(temp, option);
                    free(temp);
                    if (!temp_result) 
                    {
                        /* handle error or return NULL */
                        return (NULL);
                    }
                }
            }
            break;
    }

    return (temp_result);
}

/**
 * create_error - Creates a string with an error line
 *
 * @errn: Number corresponding to the type of error
 * @shell_info: Struct containing shell information
 * @exit_num: Value of exit the shell should have
 * Return: 0 success, -1 fail
 */
int create_error(int errn, ShellInfo *shell_info, int exit_num)
{
    char *result;
    char *temp_result;
    int error_count;
    char *current_command;
    char **command_options;
    char *shell_name;
    char *error_messages[10];
    
    error_count = *(shell_info->error_count);
    current_command = shell_info->current_command;
    command_options = shell_info->command_options;
    shell_name = shell_info->shell_name;
    error_messages[] =
    {
        "not found",
        "Permission denied",
        "Illegal number",
        "name is NULL, points to a string of len 0, or has an '=' char.",
        "can't cd to ",
        "Illegal option ",
        "Help command error",
        "Error allocating memory",
        "Wrong Alias",
        NULL
    };

   
    
    result = concatenate_strings(shell_name, ": ");
    if (!result) 
    {
        return (handle_error(7, shell_info, (1)));
    }

    temp_result = concatenate_strings(result, _itoa(error_count));
    free(result);

    if (!temp_result) 
    {
        return (handle_error(7, shell_info, (1)));
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
        return (handle_error(7, shell_info, (1)));
    }

    {
        int length = 0;  /* Move declaration to the beginning */
        while (temp_result[length] != '\0') 
        {
            length++;
        }

        write(2, temp_result, length);
        write(2, "\n", (1));
    }

    free(temp_result);
    *(shell_info->exit_number) = exit_num;
    return (0);
}
