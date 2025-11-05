#include "shell.h"

/**
* read_command - Reads a command from stdin
* @buffer: Buffer to store the command
* @size: Size of the buffer
*
* Return: Number of characters read, or -1 on EOF
*/
ssize_t read_command(char *buffer, size_t size)
{
ssize_t nread;

nread = getline(&buffer, &size, stdin);

if (nread == -1)
return (-1);

if (nread > 0 && buffer[nread - 1] == '\n')
buffer[nread - 1] = '\0';

return (nread);
}

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
* execute_command - Executes a command
* @command: The command to execute
*
* Return: 0 on success, -1 on error
*/
int execute_command(char *command)
{
pid_t pid;
int status;
char *argv[2];
char *trimmed;

trimmed = trim_whitespace(command);

if (trimmed == NULL || trimmed[0] == '\0')
return (0);

pid = fork();

if (pid == -1)
{
perror("./shell");
return (-1);
}
else if (pid == 0)
{
argv[0] = trimmed;
argv[1] = NULL;

if (execve(trimmed, argv, environ) == -1)
{
fprintf(stderr, "./shell: No such file or directory\n");
exit(127);
}
}
else
{
waitpid(pid, &status, 0);
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
size_t bufsize = MAX_CMD_LEN;
ssize_t nread;
int interactive;

buffer = malloc(bufsize);
if (buffer == NULL)
{
perror("malloc");
return (1);
}

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

execute_command(buffer);
}

free(buffer);
return (0);
}
