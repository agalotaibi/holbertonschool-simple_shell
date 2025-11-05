#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

extern char **environ;
int execute_command(char *command);
ssize_t read_command(char *buffer, size_t size);

#endif /* SHELL_H */
