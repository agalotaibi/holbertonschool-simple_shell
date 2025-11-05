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
while (buffer[start] == ' ' || buffer[start] == '\t')
start++;
end = strlen(buffer) - 1;
while (end >= start && (buffer[end] == ' ' || buffer[end] == '\t'))
end--;
buffer[end + 1] = '\0';
if (start > 0)
memmove(buffer, buffer + start, end - start + 2);
if (buffer[0] == '\0')
continue;
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
