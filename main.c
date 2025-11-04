#include "shell.h"

/**
* main - Entry point for the simple shell program.
* Return: Always 0 on success.
*/
int main(void)
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t chars_read = 0;
pid_t child_pid;
char *argv[2];

while (1)
{
if (isatty(STDIN_FILENO))
printf("#cisfun$ ");
chars_read = getline(&buffer, &bufsize, stdin);
if (chars_read == -1) 
{
if (isatty(STDIN_FILENO))
printf("\n");
break;
}
buffer[chars_read - 1] = '\0';
child_pid = fork();
if (child_pid == -1)
{
perror("Error");
break;
}
if (child_pid == 0) 
{
argv[0] = buffer;
argv[1] = NULL;
if (execve(buffer, argv, environ) == -1)
{
if (isatty(STDIN_FILENO))
perror("./shell");
exit(1);
}
}
else
{
wait(NULL);
}
}
free(buffer);
return (0);
}
