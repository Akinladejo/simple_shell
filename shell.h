#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>

// Struct containing vital shell information
typedef struct ShellInfo {
    char *name;
    char *inputLine;
    char *directive;
    char **options;
    char *directivePath;
    int *errorCount;
    int *exitNumber;
    int *logicalRelation;
    int *isRunnable;
    struct ShellInfo *nextDirective;
    char ***envCopy;
    int *unsetNull;
} ShellInfo;

// Struct for built-ins
typedef struct BuiltInOperations {
    char *directive;
    ssize_t (*function)(ShellInfo *shell);
} BuiltIns;

// Struct for built-ins
typedef struct Assistance {
    char *directive;
    void (*helpFunction)(void);
} HelpInfo;

// Function Declarations

// Environment Operations
char *_fetchEnvironment(const char *name, char **env);
char *_locatePath(char *directive, char **env, ShellInfo *shell);

// String Operations
char *_duplicateString(char *str);
char *concatenateStrings(char *s1, char *s2);
size_t _stringLength(const char *s);
char *_copyString(char *destination, const char *source);
char *_tokenizeString(char *str, const char *delim);

// Directive Operations
char **fetchParameters(char *inputLine, ShellInfo *shell);
int executeDirective(char *program, char *directive[], char **env, ShellInfo *shell);
void addDirectiveToShell(ShellInfo *shell, char *inputLine, char *directive, char **parameters);
void addPathToDirective(ShellInfo *shell, char *pathDirective);

// Input Handling
ssize_t fetchLine(char **inputLine, size_t *bufSize, int fd);
void freeDoublePointer(char **p);
size_t stringArrayLength(char **array);
char **checkInput(int argc, char **argv, size_t *bufSize, char **inputLine, ShellInfo *shell);

// Shell Initialization and Error Handling
ShellInfo *initializeShellInfo(char *argv0, int *errCount, int *exitNum,
                               int *relation, int *runnable, char ***env, int *unsetNull);
int handleShellError(int errCount, ShellInfo *shell, int exitNum);

// Built-in Operations
ssize_t runBuiltInOperations(ShellInfo *shell);
ssize_t exitDirective(ShellInfo *shell);
ssize_t helpDirective(ShellInfo *shell);

// String Comparison and Conversion
int compareStrings(const char *s1, const char *s2);
long convertToInteger(const char *s);
long calculatePower(long base, long exponent);

// String Array Operations
char **copyStringArray(char **array, size_t oldSize, size_t newSize);

// Environment Variable Operations
char **setEnvironmentVariable(char **env, const char *variable, const char *value, ShellInfo *shell);
char **unsetEnvironmentVariable(char **env, const char *variable, ShellInfo *shell);

// Numeric Operations
int isDigit(int c);
int isNumericString(const char *s);

// Directory Operations
ssize_t changeDirectory(ShellInfo *shell);

// Comment Removal
char *removeComment(char *str);

// Display Operations
void displayString(const char *s);
void helpUnsetEnvironment(void);
void helpChangeDirectory(void);
void helpHelp(void);
void helpAlias(void);
void showHelp(void);

#endif
