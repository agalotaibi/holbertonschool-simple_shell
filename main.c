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

token = strtok(line, " \t\n\r");
while (token != NULL && argc < MAX_ARGS - 1)
{
argv[argc++] = token;
token = strtok(NULL, " \t\n\r");
}
argv[argc] = NULL;

return (argc);
}

/**
* execute_command - Executes a command
* @line: The command line to execute
*
* Return: 0 on success, -1 on error
*/
int execute_command(char *line)
{
pid_t pid;
int status;
char *argv[MAX_ARGS], *command_path = NULL;
int argc;

if (line == NULL || line[0] == '\0')
return (0);

argc = parse_command(line, argv);
if (argc == 0)
return (0);

command_path = get_location(argv[0]);

if (command_path == NULL)
{
	fprintf(stderr, "./shell: %s: command not found\n.", argv[0]);
	return (0);
}

pid = fork();

if (pid == -1)
{
perror("./shell");
free(command_path);
return (-1);
}
else if (pid == 0)
{
if (execve(command_path, argv, environ) == -1)
{
fprintf(stderr, "./shell: No such file or directory\n");
free(command_path);
exit(127);
}
}
else
{
waitpid(pid, &status, 0);
free(command_path);
}

return (0);
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
execute_command(cmd_copy);
free(cmd_copy);
}
}
}
}

free(buffer);
return (0);
}

