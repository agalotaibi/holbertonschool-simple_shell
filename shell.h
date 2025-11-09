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

extern char **environ;
int execute_command(char *command);
ssize_t read_command(char *buffer, size_t size);
char *trim_whitespace(char *str);
char *get_location(char *command);

#endif /* SHELL_H */
