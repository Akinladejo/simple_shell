#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environment variable */
extern char **global_environment;
/* Global program name */
char *program_name;
/* Global history counter */
int history_count;

/**
 * struct path_node - A new struct type defining a linked list for directories in the PATH.
 * @directory: A directory path.
 * @next: A pointer to another struct path_node.
 */
typedef struct path_node
{
    char *directory;
    struct path_node *next;
} path_node_t;

/**
 * struct builtin_command - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @function: A function pointer to the builtin command's function.
 */
typedef struct builtin_command
{
    char *name;
    int (*function)(char **arguments, char **front);
} builtin_command_t;

/**
 * struct shell_alias - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct shell_alias.
 */
typedef struct shell_alias
{
    char *name;
    char *value;
    struct shell_alias *next;
} shell_alias_t;

/* Global aliases linked list */
shell_alias_t *aliases_list;

/* Main Helpers */
ssize_t read_line(char **lineptr, size_t *n, FILE *stream);
void *resize_memory(void *ptr, unsigned int old_size, unsigned int new_size);
char **tokenize_string(char *line, char *delimiter);
char *find_command_location(char *command);
path_node_t *get_path_directories(char *path);
int execute_command(char **arguments, char **front);
void free_path_list(path_node_t *head);
char *integer_to_string(int num);

/* Input Helpers */
void process_line(char **line, ssize_t read_size);
void replace_variables(char **arguments, int *execution_return);
char *parse_arguments(char *line, int *execution_return);
int execute_arguments(char **arguments, char **front, int *execution_return);
int run_shell(int *execution_return);
int validate_arguments(char **arguments);
void free_arguments(char **arguments, char **front);
char **substitute_aliases(char **arguments);

/* String functions */
int string_length(const char *s);
char *string_concatenate(char *destination, const char *source);
char *string_concatenate_n(char *destination, const char *source, size_t n);
char *string_copy(char *destination, const char *source);
char *find_character(char *s, char c);
int string_span(char *s, char *accept);
int string_compare(char *s1, char *s2);
int string_compare_n(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin_command(char *command))(char **arguments, char **front);
int exit_shell(char **arguments, char **front);
int show_environment(char **arguments, char __attribute__((__unused__)) **front);
int set_environment(char **arguments, char __attribute__((__unused__)) **front);
int unset_environment(char **arguments, char __attribute__((__unused__)) **front);
int change_directory(char **arguments, char __attribute__((__unused__)) **front);
int manage_alias(char **arguments, char __attribute__((__unused__)) **front);
int show_help(char **arguments, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **copy_environment(void);
void release_environment(void);
char **get_environment_variable(const char *variable);

/* Error Handling */
int generate_error(char **arguments, int error_code);
char *error_message_environment(char **arguments);
char *error_message_1(char **arguments);
char *error_message_2_exit(char **arguments);
char *error_message_2_cd(char **arguments);
char *error_message_2_syntax(char **arguments);
char *error_message_126(char **arguments);
char *error_message_127(char **arguments);

/* Linkedlist Helpers */
shell_alias_t *add_alias_end(shell_alias_t **head, char *name, char *value);
void free_alias_list(shell_alias_t *head);
path_node_t *add_node_end(path_node_t **head, char *directory);
void free_path_list(path_node_t *head);

void provide_help(void);
void help_alias_command(void);
void help_change_directory(void);
void help_exit_command(void);
void help_help_command(void);
void help_show_environment(void);
void help_set_environment(void);
void help_unset_environment(void);
void help_show_history(void);

int process_file_commands(char *file_path, int *execution_return);
#endif /* SHELL_H */
