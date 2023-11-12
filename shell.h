#ifndef CUSTOM_SHELL_H
#define CUSTOM_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 128
#define TOKEN_DELIMITER " \t\r\n\a"

extern char **custom_environment;

/**
 * struct RuntimeData - Struct holding runtime information.
 * @arguments: Argument vector.
 * @user_input: User-entered command line.
 * @tokens: Tokenized command line.
 * @execution_status: Last shell execution status.
 * @line_counter: Counter for lines processed.
 * @environment_variables: Array of environment variables.
 * @process_id: Process ID of the shell.
 */
typedef struct RuntimeData {
    char **arguments;
    char *user_input;
    char **tokens;
    int execution_status;
    int line_counter;
    char **environment_variables;
    char *process_id;
} RuntimeData;

/**
 * struct SeparatorList - Single linked list to store separators.
 * @separator: Separator character (;, |, or &).
 * @next: Pointer to the next node in the list.
 */
typedef struct SeparatorList {
    char separator;
    struct SeparatorList *next;
} SeparatorList;

/**
 * struct LineList - Single linked list to store command lines.
 * @command_line: Command line string.
 * @next: Pointer to the next node in the list.
 */
typedef struct LineList {
    char *command_line;
    struct LineList *next;
} LineList;

/**
 * struct RuntimeVarList - Single linked list to store variables.
 * @variable_length: Length of the variable.
 * @value: Value of the variable.
 * @value_length: Length of the value.
 * @next: Pointer to the next node in the list.
 */
typedef struct RuntimeVarList {
    int variable_length;
    char *value;
    int value_length;
    struct RuntimeVarList *next;
} RuntimeVarList;

/**
 * struct BuiltinCommand - Struct for built-in command information.
 * @name: Name of the built-in command (e.g., cd, exit, env).
 * @function_pointer: Pointer to the function implementing the command.
 */
typedef struct BuiltinCommand {
    char *name;
    int (*function_pointer)(RuntimeData *runtime_data);
} BuiltinCommand;

/* Function Prototypes */

/* Auxiliary Lists */
SeparatorList *add_separator_node_end(SeparatorList **head, char sep);
void free_separator_list(SeparatorList **head);

LineList *add_line_node_end(LineList **head, char *line);
void free_line_list(LineList **head);

RuntimeVarList *add_runtime_var_node(RuntimeVarList **head, int length_variable, char *variable, int length_value);
void free_runtime_var_list(RuntimeVarList **head);

/* Auxiliary String Functions */
char *_custom_strcat(char *destination, const char *source);
char *_custom_strcpy(char *destination, char *source);
int _custom_strcmp(char *string1, char *string2);
char *_custom_strchr(char *string, char character);
int _custom_strspn(char *string, char *accepted_characters);

/* Auxiliary Memory */
void _custom_memcpy(void *new_pointer, const void *pointer, unsigned int size);
void *_custom_realloc(void *pointer, unsigned int old_size, unsigned int new_size);
char **_custom_realloc_double_pointer(char **pointer, unsigned int old_size, unsigned int new_size);

/* Auxiliary String 2 */
char *_custom_strdup(const char *string);
int _custom_strlen(const char *string);
int compare_chars(char string[], const char *delimiter);
char *_custom_strtok(char string[], const char *delimiter);
int _custom_isdigit(const char *string);

/* Auxiliary String 3 */
void reverse_string(char *string);

/* Check Syntax Error */
int has_repeated_char(char *input, int index);
int has_syntax_error_separator_operator(char *input, int index, char last);
int is_first_char(char *input, int *index);
void print_syntax_error(RuntimeData *runtime_data, char *input, int index, int boolean_value);
int check_syntax_error(RuntimeData *runtime_data, char *input);

/* Shell Loop */
char *remove_comment(char *input);
void run_shell_loop(RuntimeData *runtime_data);

/* Read Line */
char *read_input_line(int *end_of_file);
ssize_t get_input_line(char **line_pointer, size_t *size, FILE *stream);

/* Split */
char *swap_characters(char *input, int boolean_value);
void add_nodes_to_lists(SeparatorList **separator_list, LineList **line_list, char *input);
void move_to_next(SeparatorList **separator_list, LineList **line_list, RuntimeData *runtime_data);
int split_commands_and_execute(RuntimeData *runtime_data, char *input);
char **split_input_line(char *input);

/* Replace Variable */
void check_environment(RuntimeVarList **head, char *input, RuntimeData *runtime_data);
int check_variables(RuntimeVarList **head, char *input, char *string, RuntimeData *runtime_data);
char *replace_input_with_variable(RuntimeVarList **head, char *input, char *new_input, int new_length);
char *replace_variable(char *input, RuntimeData *runtime_data);

/* Get Input Line */
void fetch_input_line(char **line_pointer, size_t *size, char *buffer, size_t j);

/* Execute Line */
int execute_line(RuntimeData *runtime_data);

/* Command Execute */
int is_current_directory(char *path, int *index);
char *find_executable_path(char *command, char **environment_variables);
int is_executable_command(RuntimeData *runtime_data);
int check_error_command(char *directory, RuntimeData *runtime_data);
int execute_command(RuntimeData *runtime_data);

/* Environment 1 */
char *_custom_getenv(const char *name, char **environment_variables);
int _custom_env(RuntimeData *runtime_data);

/* Environment 2 */
char *copy_information(char *name, char *value);
void set_environment_variable(char *name, char *value, RuntimeData *runtime_data);
int set_environment(RuntimeData *runtime_data);
int unset_environment(RuntimeData *runtime_data);

/* Change Directory */
void change_directory_dot(RuntimeData *runtime_data);
void change_directory_to(RuntimeData *runtime_data);
void change_directory_previous(RuntimeData *runtime_data);
void change_directory_to_home(RuntimeData *runtime_data);

/* Change Directory Shell */
int change_directory_shell(RuntimeData *runtime_data);

/* Get Builtin Command */
int (*get_builtin_command(char *command))(RuntimeData *runtime_data);

/* Exit Custom Shell */
int exit_custom_shell(RuntimeData *runtime_data);

/* Auxiliary Stdlib */
int get_length(int number);
char *custom_itoa(int number);
int custom_atoi(char *string);

/* Auxiliary Error 1 */
char *custom_strcat_change_directory(RuntimeData *, char *, char *, char *);
char *error_get_change_directory(RuntimeData *runtime_data);
char *error_not_found_command(RuntimeData *runtime_data);
char *error_exit_custom_shell(RuntimeData *runtime_data);

/* Auxiliary Error 2 */
char *error_get_alias_command(char **arguments);
char *error_environment(RuntimeData *runtime_data);
char *error_syntax(RuntimeData *runtime_data);
char *error_permission(RuntimeData *runtime_data);
char *error_path_126(RuntimeData *runtime_data);

/* Get Custom Shell Error */
int get_custom_shell_error(RuntimeData *runtime_data, int evaluation);

/* Get Sigint */
void handle_sigint(int signal);

/* Auxiliary Help */
void print_help_environment(void);
void print_help_set_environment(void);
void print_help_unset_environment(void);
void print_help_general(void);
void print_help_exit(void);

/* Auxiliary Help 2 */
void print_help(void);
void print_help_alias(void);
void print_help_change_directory(void);

/* Get Help Information */
int get_help_information(RuntimeData *runtime_data);

#endif
