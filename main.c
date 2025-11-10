#include "shell.h"
#define MAX_ARGS 64

/**
* trim_whitespace - Removes leading and trailing whitespace
* @str: String to trim
*
* Return: Pointer to trimmed string
*/
char *trim_whitespace(char *str)
{
char *end;

while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
str++;

if (*str == '\0')
return (str);

end = str + strlen(str) - 1;
while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
end--;

*(end + 1) = '\0';

return (str);
}

/**
* parse_command - Parses command line into arguments
* @line: Command line to parse
* @argv: Array to store argument pointers
*
* Return: Number of arguments parsed
*/
int parse_command(char *line, char **argv)
{
int argc = 0;
char *token;

token = strtok(line, " \t\n\r\"'");
while (token != NULL && argc < MAX_ARGS - 1)
{
argv[argc++] = token;
token = strtok(NULL, " \t\n\r\"'");
}
argv[argc] = NULL;

return (argc);
}
/**
* main - Entry point for the simple shell
*
* Return: Always 0
*/
int main(void)
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t nread;
int interactive;
int status;

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
