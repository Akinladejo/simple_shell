#ifndef CUSTOM_SHELL_H
#define CUSTOM_SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024
extern char **environ;

/**
 * PathNode struct - a linked list to store directories in the PATH
 * @dir_path: the directory path in the format /usr/bin
 * @dir_length: the length of the directory string
 * @next: pointer to the next node in the linked list
 */
typedef struct PathNode
{
    char *dir_path;
    unsigned int dir_length;
    struct PathNode *next;
} PathNode;

/**
 * BuiltinCommand struct - a structure for function pointers to built-in commands
 * @command_str: the command string (env, cd, alias, history)
 * @fun: function pointer to the respective command function
 */
typedef struct BuiltinCommand
{
    char *command_str;
    int (*fun)();
} BuiltinCommand;

/* In builtins.c */
int (*is_builtin(char *command))();
int graceful_exit(char **tokens, PathNode *path_list, char *buffer);
int display_environment(char **tokens, PathNode *environment);
int change_directory(char **tokens);

/* In builtins_2.c */
int set_user_environment(char **tokens);
int handle_alias(void);
int show_history(void);
int custom_function(void);

/* in environment.c */
PathNode *create_path_list(void);
PathNode *initialize_environment(void);
char *search_command_in_path(char *cmd, PathNode *path_list);

/* in env_operations.c */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);

/* in linked_list_operations.c */
PathNode *add_node(PathNode **head, char *path, unsigned int length);
void free_path_list(PathNode *head);

/* In executor.c */
void execute_command(char *argv[], PathNode *path_list);

/* In memory_management.c */
void *_realloc_memory(char *ptr, unsigned int old_size, unsigned int new_size);
void _memset_memory(char *str, int fill, int n);
void _memcpy_memory(char *destination, char *source, unsigned int bytes);

/* In parser.c */
char *_read_line(int file);
char **parse_arguments(char *str, char *delim);
void read_input(void);

/* In strtok.c */
/* Functions in this file are not referenced elsewhere. */
char *_strtok_r(char *str, char *delim, char **saveptr);

/* In string_operations.c */
int _string_length(char *s);
int _string_compare(char *s1, char *s2, size_t bytes);
char *_string_duplicate(char *src);
char *_string_concat_realloc(char *destination, char *source);
int _convert_to_integer(char *s);
int _is_digit(int c);

/* In string_operations_2.c */
unsigned int count_words(char *str);
void print_simple(const char *str);
int _string_length_const(const char *s);
size_t print_linked_list(const PathNode *h);

#endif
