#include "shell.h"

int main(void)
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t chars_read;
pid_t child_pid;
char **argv;

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

argv = parse_input(buffer);

child_pid = fork();
if (child_pid == -1)
{
perror("fork");
break;
}

if (child_pid == 0)
{
execve(argv[0], argv, environ);
perror("./shell");
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
