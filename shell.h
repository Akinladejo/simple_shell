#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>

/**
 * @struct ShellInfo
 * @brief Structure containing important shell information
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
 * @struct BuiltIn
 * @brief Structure for built-in commands
 */
typedef struct BuiltIn
{
    char *command;
    ssize_t (*function)(ShellInfo *shell_info);
} BuiltIn;

/**
 * @struct HelpInfo
 * @brief Structure for built-in help commands
 */
typedef struct HelpInfo
{
    char *built_in_command;
    void (*help_function)(void);
} HelpInfo;

/**
 * @brief Get the value of an environment variable
 */
char *_get_environment_variable(const char *name, char **env);

/**
 * @brief Get the absolute path of a command
 */
char *_get_absolute_path(char *command, char **env, ShellInfo *shell_info);

/**
 * @brief Duplicate a string
 */
char *_str_duplicate(char *str);

/**
 * @brief Concatenate two strings
 */
char *concatenate_strings(char *s1, char *s2);

/**
 * @brief Get the length of a string
 */
int string_length(char *s);

/**
 * @brief Copy a string
 */
char *_string_copy(char *destination, char *source);

/**
 * @brief Tokenize a string
 */
char *_string_token(char *str, const char *delimiter);

/**
 * @brief Get parameters from a buffer
 */
char **get_parameters(char *buffer, ShellInfo *shell_info);

/**
 * @brief Execute a command
 */
int execute_command(char *program, char *command[], char **env, ShellInfo *shell_info);

/**
 * @brief Handle a signal
 */
void handle_signal(int signal_number);

/**
 * @brief Handle another signal
 */
void handle_signal2(int signal_number);

/**
 * @brief Get a line of input
 */
int get_line(char **buffer, size_t *buffer_size, int file_descriptor);

/**
 * @brief Free a double pointer
 */
void free_double_pointer(char **pointer);

/**
 * @brief Get the length of a string array
 */
int string_array_length(char **array);

/**
 * @brief Check and process input
 */
char **check_input(int argument_count, char **arguments, size_t *buffer_size,
                   char **buffer, ShellInfo *shell_info);

/**
 * @brief Initialize the shell information structure
 */
ShellInfo *initialize_shell_info(char *argv0, int *error_number, int *exit_number,
                                 int *logical_relation, int *is_runnable, char ***environment, int *unset_environment);

/**
 * @brief Handle errors
 */
int handle_error(int error_number, ShellInfo *shell_info, int exit_number);

/**
 * @brief Add a command to the shell information
 */
void add_command(ShellInfo *shell_info, char *input_buffer, char *command, char **parameters);

/**
 * @brief Add a path to the current command
 */
void add_path_to_command(ShellInfo *shell_info, char *path_command);

/**
 * @brief Execute built-in commands
 */
ssize_t execute_built_ins(ShellInfo *shell_info);

/**
 * @brief Handle the exit command
 */
ssize_t exit_command(ShellInfo *shell_info);

/**
 * @brief Compare two strings
 */
int compare_strings(char *string1, char *string2);

/**
 * @brief Convert a string to an integer
 */
long convert_to_integer(char *string);

/**
 * @brief Calculate the power of a number
 */
long power(long base, long exponent);

/**
 * @brief Copy a double pointer with resizing
 */
char **copy_double_pointer(char **pointer, int old_size, int new_size);

/**
 * @brief Set an environment variable
 */
char **set_environment_variable(char **env, char *variable, char *value, ShellInfo *shell_info);

/**
 * @brief Unset an environment variable
 */
char **unset_environment_variable(char **env, char *variable, ShellInfo *shell_info);

/**
 * @brief Check if a character is a digit
 */
int is_digit(int character);

/**
 * @brief Check if a string is a number
 */
int is_number(char *string);

/**
 * @brief Change the current directory
 */
ssize_t change_directory(ShellInfo *shell_info);

/**
 * @brief Remove comments from a string
 */
char *remove_comments(char *string);

/**
 * @brief Handle the help command
 */
ssize_t help_command(ShellInfo *shell_info);

/**
 * @brief Print a string
 */
void print_string(char *string);

/**
 * @brief Display help for the unsetenv command
 */
void display_help_unsetenv(void);

/**
 * @brief Display help for the cd command
 */
void display_help_change_directory(void);

/**
 * @brief Display help for the help command
 */
void display_help_help(void);

/**
 * @brief Display help for the alias command
 */
void display_help_alias(void);

/**
 * @brief Print general help
 */
void print_help(void);

#endif
