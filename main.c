#include "shell.h"

int main(void)
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t chars_read;
pid_t child_pid;
char **argv;
int start = 0;
int end;

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

if (buffer[chars_read - 1] == '\n')
buffer[chars_read - 1] = '\0';

if (buffer[0] == '\0' || strspn(buffer, " \t") == strlen(buffer))
continue;

argv = parse_input(buffer);
if (argv == NULL || argv[0] == NULL)
{
free(argv);
continue;
}

child_pid = fork();
if (child_pid == -1)
{
perror("fork");
break;
}

if (child_pid == 0)
{
execve(argv[0], argv, environ);
perror(argv[0]);
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}

free(argv);
}

free(buffer);
return (0);
}
