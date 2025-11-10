#include "shell.h"
#define MAX_ARGS 64
/**
* main - Entry point for the simple shell
* Return: Always 0
*/
int main(void)
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t nread;
int interactive, status;

interactive = isatty(STDIN_FILENO);
while (1)
{
if (interactive)
{
printf("#cisfun$ ");
fflush(stdout);
}
nread = getline(&buffer, &bufsize, stdin);
if (nread == -1)
{
if (interactive)
printf("\n");
break;
}
if (nread > 0 && buffer[nread - 1] == '\n')
buffer[nread - 1] = '\0';
{
char *trimmed = trim_whitespace(buffer);

if (trimmed[0] != '\0')
{
char *cmd_copy = strdup(trimmed);

if (cmd_copy != NULL)
{
if (strcmp(cmd_copy, "env") == 0)
{
print_env();
free(cmd_copy);
continue;
}
if (strcmp(cmd_copy, "exit") == 0)
{
free(cmd_copy);
free(buffer);
exit(0);
}
status = execute_command(cmd_copy);
free(cmd_copy);
if (!interactive && status != 0)
{
free(buffer);
exit(status);
}
}
}
}
}
free(buffer);
return (0);
}
