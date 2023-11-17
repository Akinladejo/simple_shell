#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>

/**
 * struct ShellInfo - Structure containing important shell information
 *
 * @shell_name: Name of the shell
 * @input_buffer: Buffer to store user input
 * @current_command: Current command being processed
 * @command_options: Array of command options
 * @command_path: Path of the command
 * @error_count: Count of errors
 * @exit_number: Exit number
 * @logical_relation: Logical relation indicator
 * @is_runnable: Indicator for command execution
 * @next_command: Pointer to the next command
 * @environment_copy: Copy of the environment variables
 * @unset_environment: Indicator for unset environment variables
 */

typedef struct ShellInfo
{
char *shell_name;
char *input_buffer;
char *current_command;
char **command_options;
char *command_path;
int *error_count;
int *exit_number;
int *logical_relation;
int *is_runnable;
struct ShellInfo *next_command;
char ***environment_copy;
int *unset_environment;
} ShellInfo;

/**
 * struct BuiltIn - Structure for built-in commands
 *
 * @command: Name of the built-in command
 * @function: Pointer to the function handling the command
 */
typedef struct BuiltIn
{
char *command;
ssize_t (*function)(ShellInfo *shell_info);
} BuiltIn;

/**
 * struct HelpInfo - Structure for built-in help commands
 *
 * @built_in_command: Name of the built-in command for help
 * @help_function: Pointer to the function displaying help
 */
typedef struct HelpInfo
{
char *built_in_command;
void (*help_function)(void);
} HelpInfo;

/**
 * _get_environment_variable - Get the value of an environment variable
 * @name: The name of the environment variable to retrieve
 * @env: The array of environment variables
 *
 * Return: The value of the specified environment var, or NULL if not found.
 */
char *_get_environment_variable(const char *name, char **env);

/**
 * _get_absolute_path - Get the absolute path of a command
 * @command: The command name to find the absolute path for
 * @env: The array of environment variables
 * @shell_info: Additional information about the shell
 *
 * Return: The absolute path of the specified command, or NULL if not found.
 */
char *_get_absolute_path(char *command, char **env, ShellInfo *shell_info);

/**
 * _str_duplicate - Duplicate a string
 * @str: The string to duplicate
 *
 * Return: A newly allocated copy of the input string.
 */
char *_str_duplicate(const char *str);

/**
 * concatenate_strings - Concatenate two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Return: A newly allocated string containing the concatenation of s1 and s2.
 */
char *concatenate_strings(const char *s1, const char *s2);

/**
 * string_length - Get the length of a string
 * @s: The input string
 *
 * Return: The length of the input string.
 */
int string_length(const char *s);

/**
 * _string_copy - Copy a string
 * @destination: The destination buffer for the copied string
 * @source: The source string to copy
 *
 * Return: A pointer to the destination buffer.
 */
char *_string_copy(char *destination, const char *source);


/**
 * _string_token - Tokenize a string
 * @str: The string to be tokenized
 * @delimiter: The delimiter used to tokenize the string
 *
 * Return: A pointer to the next token in the string
 */
char *_string_token(char *str, const char *delimiter);

/**
 * get_parameters - Get parameters from a buffer
 * @buffer: The buffer containing the parameters
 * @shell_info: Additional information about the shell
 *
 * Return: An array of strings representing the parameters
 */
char **get_parameters(char *buffer, ShellInfo *shell_info);

/**
 * execute_command - Execute a command
 * @program: The program to be executed
 * @command: An array of strings representing the command and its arguments
 * @env: The array of environment variables
 * @shell_info: Additional information about the shell
 *
 * Return: The exit status of the executed command.
 */
int execute_command(char *program, char *command[], char **env, ShellInfo *shell_info);

/**
 * handle_signal - Handle a signal
 * @signal_number: The signal number to handle
 */
void handle_signal(int signal_number);

/**
 * handle_signal2 - Handle another signal
 * @signal_number: The signal number to handle
 */
void handle_signal2(int signal_number);

/**
 * get_line - Get a line of input
 * @buffer: A pointer to the buffer that will store the input line
 * @buffer_size: A pointer to the size of the buffer
 * @file_descriptor: The file descriptor from which to read the input
 *
 * Return: The number of characters read, or -1 on failure.
 */
int get_line(char **buffer, size_t *buffer_size, int file_descriptor);

/**
 * free_double_pointer - Free a double pointer
 * @pointer: The double pointer to be freed
 */
void free_double_pointer(char **pointer);

/**
 * string_array_length - Get the length of a string array
 * @array: The input string array
 *
 * Return: The number of strings in the array.
 */
int string_array_length(char **array);


/**
 * check_input - Check and process input
 * @argument_count: The number of arguments passed to the program
 * @arguments: An array of strings representing the program arguments
 * @buffer_size: A pointer to the size of the input buffer
 * @buffer: A pointer to the input buffer
 * @shell_info: Additional information about the shell
 *
 * Return: An array of strings representing the processed input.
 */
char **check_input(int argument_count, char **arguments, size_t *buffer_size,
char **buffer, ShellInfo *shell_info);

/**
 * get_user_input - Get user input
 * @buffer_size: A pointer to the size of the input buffer
 * @buffer: A pointer to the input buffer
 * @shell_info: Additional information about the shell
 *
 * Return: An array of strings representing the user input.
 */
char **get_user_input(size_t *buffer_size, char **buffer,
ShellInfo *shell_info);

/**
 * initialize_shell_info - Initialize the shell information structure
 * @argv0: The name of the program
 * @error_number: A pointer to the error number variable
 * @exit_number: A pointer to the exit number variable
 * @logical_relation: A pointer to the logical relation variable
 * @is_runnable: A pointer to the is_runnable variable
 * @environment: A pointer to the environment variable array
 * @unset_environment: A pointer to the unset_environment variable
 *
 * Return: A pointer to the initialized ShellInfo structure.
 */
ShellInfo *initialize_shell_info(char *argv0, int *error_number,
int *exit_number,
int *logical_relation,
int *is_runnable,
char ***environment,
int *unset_environment);

/**
 * _realloc - Reallocate memory for a pointer
 * @ptr: The pointer to reallocate
 * @old_size: The old size of the memory block
 * @new_size: The new size to allocate
 *
 * Return: A pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/**
 * read_file_into_buffer - Read a file into a buffer
 * @buf: A pointer to the buffer
 * @len: A pointer to the length of the buffer
 * @size: The size to read from the file
 * @file_descriptor: The file descriptor to read from
 *
 * Return: The number of bytes read into the buffer.
 */
int read_file_into_buffer(char **buf, size_t *len, size_t size,
int file_descriptor);

/**
 * resize_buffer - Resize a buffer
 * @buf: A pointer to the buffer
 * @size: A pointer to the size of the buffer
 *
 * Return: The size of the resized buffer.
 */
int resize_buffer(char **buf, size_t *size);

/**
 * process_buffer - Process a buffer
 * @buf: The buffer to process
 * @len: The length of the buffer
 * @buffer: A pointer to the input buffer
 * @buffer_size: A pointer to the size of the input buffer
 * @size: A pointer to the size of the buffer
 *
 * Return: The processed buffer.
 */
int process_buffer(char *buf, size_t len, char **buffer,
size_t *buffer_size, size_t *size);

/**
 * handle_error - Handle errors
 * @error_number: The error number
 * @shell_info: Additional information about the shell
 * @exit_number: The exit number
 *
 * Return: The exit status.
 */
int handle_error(int error_number, ShellInfo *shell_info, int exit_number);

/**
 * add_command - Add a command to the shell information
 * @shell_info: Additional information about the shell
 * @input_buffer: The input buffer
 * @command: The command to add
 * @parameters: An array of strings representing the command parameters
 */
void add_command(ShellInfo *shell_info, char *input_buffer, char *command,
char **parameters);

/**
 * add_path_to_command - Add a path to the current command
 * @shell_info: Additional information about the shell
 * @path_command: The path to add to the current command
 */
void add_path_to_command(ShellInfo *shell_info, char *path_command);

/**
 * execute_built_ins - Execute built-in commands
 * @shell_info: Additional information about the shell
 *
 * Return: The result of the built-in command execution.
 */
ssize_t execute_built_ins(ShellInfo *shell_info);

/**
 * auxiliary_cd - Change directory (auxiliary function)
 * @shell_info: Additional information about the shell
 * @current_directory: The current directory
 *
 * Return: A pointer to the new current directory.
 */
char *auxiliary_cd(ShellInfo *shell_info, char *current_directory);

/**
 * auxiliary_cd_2 - Change directory (auxiliary function)
 * @shell_info: Additional information about the shell
 * @current_directory: The current directory
 *
 * Return: A pointer to the new current directory.
 */
char *auxiliary_cd_2(ShellInfo *shell_info, char *current_directory);

/**
 * cd_command - Change directory command
 * @shell_info: Additional information about the shell
 *
 * Return: The result of the change directory command.
 */
ssize_t cd_command(ShellInfo *shell_info);


/**
 * exit_command - Handle the exit command
 * @shell_info: Additional information about the shell
 *
 * Return: The result of the exit command.
 */
ssize_t exit_command(ShellInfo *shell_info);

/**
 * compare_strings - Compare two strings
 * @string1: The first string
 * @string2: The second string
 *
 * Return: An integer less than, equal to'
 */
int compare_strings(char *string1, char *string2);

/**
 * convert_to_integer - Convert a string to an integer
 * @string: The string to be converted
 *
 * Return: The converted integer value.
 */
long convert_to_integer(char *string);

/**
 * power - Calculate the power of a number
 * @base: The base of the power
 * @exponent: The exponent of the power
 *
 * Return: base to the power of the exponent.
 */
long power(long base, long exponent);

/**
 * copy_double_pointer - Copy a double pointer with resizing
 * @pointer: The double pointer to be copied
 * @old_size: The old size of the double pointer
 * @new_size: The new size to allocate
 *
 * Return: A new double pointer with resized content.
 */
char **copy_double_pointer(char **pointer, int old_size, int new_size);

/**
 * set_environment_variable - Set an environment variable
 * @env: The array of environment variables
 * @variable: The name of the environment variable to set
 * @value: The value to assign to the environment variable
 * @shell_info: Additional information about the shell
 *
 * Return: The updated array of environment variables.
 */
char **set_environment_variable(char **env, char *variable, char *value,
ShellInfo *shell_info);

/**
 * search_environment_variable - Search for an environment variable
 * @env: The array of environment variables
 * @variable: The name of the environment variable to search for
 *
 * Return: The index of the environment variable if found
 */
int search_environment_variable(char **env, char *variable);

/**
 * unset_environment_variable - Unset an environment variable
 * @env: The array of environment variables
 * @variable: The name of the environment variable to unset
 * @shell_info: Additional information about the shell
 *
 * Return: The updated array of environment variables.
 */
char **unset_environment_variable(char **env, const char *variable,
ShellInfo *shell_info);

/**
 * is_digit - Check if a character is a digit
 * @character: The character to check
 *
 * Return: 1 if the character is a digit, 0 otherwise.
 */
int is_digit(int character);

/**
 * is_number - Check if a string is a number
 * @string: The string to check
 *
 * Return: 1 if the string is a number, 0 otherwise.
 */
int is_number(char *string);

/**
 * change_directory - Change the current directory
 * @shell_info: Additional information about the shell
 *
 * Return: The result of the change directory operation.
 */
ssize_t change_directory(ShellInfo *shell_info);

/**
 * determine_directory - Determine the target directory
 * @shell_info: Additional information about the shell
 * @current_directory: The current working directory
 *
 * Return: A pointer to the target directory.
 */
char *determine_directory(ShellInfo *shell_info,
const char *current_directory);

/**
 * chang_directory - Change the current directory
 * @directory: The target directory to change to
 * @shell_info: Additional information about the shell
 *
 * Return: The result of the change directory operation.
 */
int chang_directory(const char *directory, ShellInfo *shell_info);

/**
 * update_environment_variables - Update environment variables.
 * @shell_info: Additional information about the shell
 * @directory: The target directory
 */
void update_environment_variables(ShellInfo *shell_info,
const char *directory);

/**
 * handle_directory_change_result - result of a directory change
 * @result: The result of the directory change operation
 * @shell_info: Additional information about the shell
 * @current_directory: The current working directory
 * @directory: The target directory
 */
void handle_directory_change_result(int result, ShellInfo *shell_info,
const char *current_directory,
const char *directory);

/**
 * free_resources - Free resources allocated during directory change
 * @shell_info: Additional information about the shell
 * @current_directory: The current working directory
 * @directory: The target directory
 */
void free_resources(ShellInfo *shell_info, char *current_directory,
                    char *directory);

/**
 * remove_comments - Remove comments from a string
 * @string: The input string with comments
 *
 * Return: A pointer to the string with comments removed.
 */
char *remove_comments(char *string);

/**
 * help_command - Handle the help command
 * @shell_info: Additional information about the shell
 *
 * Return: The result of the help command.
 */
ssize_t help_command(ShellInfo *shell_info);

/**
 * print_string - Print a string
 * @string: The string to be printed
 */
void print_string(char *string);

/**
 * display_help_unsetenv - Display help for the unsetenv command
 */
void display_help_unsetenv(void);

/**
 * display_help_change_directory - Display help for the cd command
 */
void display_help_change_directory(void);

/**
 * display_help_help - Display help for the help command
 */
void display_help_help(void);

/**
 * display_help_alias - Display help for the alias command
 */
void display_help_alias(void);

/**
 * print_help - Print general help
 */
void print_help(void);

#endif
