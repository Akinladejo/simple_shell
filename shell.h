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
typedef struct ShellInfo {
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
typedef struct BuiltIn {
	char *command;
	ssize_t (*function)(ShellInfo *shell_info);
} BuiltIn;

/**
 * struct HelpInfo - Structure for built-in help commands
 *
 * @built_in_command: Name of the built-in command for help
 * @help_function: Pointer to the function displaying help
 */
typedef struct HelpInfo {
	char *built_in_command;
	void (*help_function)(void);
} HelpInfo;

/**
 * _get_environment_variable - Get the value of an environment variable
 */
char *_get_environment_variable(const char *name, char **env);

/**
 * _get_absolute_path - Get the absolute path of a command
 */
char *_get_absolute_path(char *command, char **env, ShellInfo *shell_info);

/**
 * _str_duplicate - Duplicate a string
 */
char *_str_duplicate(char *str);

/**
 * concatenate_strings - Concatenate two strings
 */
char *concatenate_strings(const char *s1, const char *s2);

/**
 * string_length - Get the length of a string
 */
int string_length(char *s);

/**
 * _string_copy - Copy a string
 */
char *_string_copy(char *destination, char *source);

/**
 * _string_token - Tokenize a string
 */
char *_string_token(char *str, const char *delimiter);

/**
 * get_parameters - Get parameters from a buffer
 */
char **get_parameters(char *buffer, ShellInfo *shell_info);

/**
 * execute_command - Execute a command
 */
int execute_command(char *program, char *command[], char **env,
		    ShellInfo *shell_info);

/**
 * handle_signal - Handle a signal
 */
void handle_signal(int signal_number);

/**
 * handle_signal2 - Handle another signal
 */
void handle_signal2(int signal_number);

/**
 * get_line - Get a line of input
 */
int get_line(char **buffer, size_t *buffer_size, int file_descriptor);

/**
 * free_double_pointer - Free a double pointer
 */
void free_double_pointer(char **pointer);

/**
 * string_array_length - Get the length of a string array
 */
int string_array_length(char **array);

/**
 * check_input - Check and process input
 */
char **check_input(int argument_count, char **arguments, size_t *buffer_size,
		   char **buffer, ShellInfo *shell_info);

/**
 * initialize_shell_info - Initialize the shell information structure
 */
ShellInfo *initialize_shell_info(char *argv0, int *error_number,
				 int *exit_number, int *logical_relation,
				 int *is_runnable, char ***environment,
				 int *unset_environment);

/**
 * handle_error - Handle errors
 */
int handle_error(int error_number, ShellInfo *shell_info, int exit_number);

/**
 * add_command - Add a command to the shell information
 */
void add_command(ShellInfo *shell_info, char *input_buffer, char *command,
		 char **parameters);

/**
 * add_path_to_command - Add a path to the current command
 */
void add_path_to_command(ShellInfo *shell_info, char *path_command);

/**
 * execute_built_ins - Execute built-in commands
 */
ssize_t execute_built_ins(ShellInfo *shell_info);

/**
 * exit_command - Handle the exit command
 */
ssize_t exit_command(ShellInfo *shell_info);

/**
 * compare_strings - Compare two strings
 */
int compare_strings(char *string1, char *string2);

/**
 * convert_to_integer - Convert a string to an integer
 */
long convert_to_integer(char *string);

/**
 * power - Calculate the power of a number
 */
long power(long base, long exponent);

/**
 * copy_double_pointer - Copy a double pointer with resizing
 */
char **copy_double_pointer(char **pointer, int old_size, int new_size);

/**
 * set_environment_variable - Set an environment variable
 */
char **set_environment_variable(char **env, char *variable, char *value,
				ShellInfo *shell_info);

/**
 * unset_environment_variable - Unset an environment variable
 */
char **unset_environment_variable(char **env, const char *variable,
				  ShellInfo *shell_info);

/**
 * is_digit - Check if a character is a digit
 */
int is_digit(int character);

/**
 * is_number - Check if a string is a number
 */
int is_number(char *string);

/**
 * change_directory - Change the current directory
 */
ssize_t change_directory(ShellInfo *shell_info);
char *determine_directory(ShellInfo *shell_info, const char *current_directory);
int chang_directory(const char *directory, ShellInfo *shell_info);
void update_environment_variables(ShellInfo *shell_info, const char *directory);
void handle_directory_change_result(int result, ShellInfo *shell_info, const char *current_directory, const char *directory);
void free_resources(ShellInfo *shell_info, char *current_directory, char *directory);

/**
 * remove_comments - Remove comments from a string
 */
char *remove_comments(char *string);

/**
 * help_command - Handle the help command
 */
ssize_t help_command(ShellInfo *shell_info);

/**
 * print_string - Print a string
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
