#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

void execute_command(char *buffer);
void trim_spaces(char *str);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);

#endif 
