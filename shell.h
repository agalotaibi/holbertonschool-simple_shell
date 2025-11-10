#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
extern char **environ;
char **parse_input(char *input);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_getenv(const char *name);
int parse_command(char *line, char **argv);
int execute_command(char *command);
ssize_t read_command(char *buffer, size_t size);
char *trim_whitespace(char *str);
char *get_location(char *command);
int check_builtin(char **argv);
void print_env(void);
#endif /* SHELL_H */
