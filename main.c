#include "shell.h"

/**
* main - Entry point for the simple shell program.
* Return: Always 0 on success.
*/
int main(void)
{
  char *input_ptr = NULL; 
char *buffer = NULL;
size_t bufsize = 0;
ssize_t chars_read;
pid_t child_pid;
char *argv[2];

while (1)
{
if (isatty(STDIN_FILENO))
printf("#cisfun$ ");

chars_read = getline(&input_ptr, &bufsize, stdin);
if (chars_read == -1)
{
if (isatty(STDIN_FILENO))
printf("\n");
break;
}

input_ptr[chars_read - 1] = '\0';
input_ptr = trim_spaces(input_ptr);

if (buffer[0] == '\0')
continue;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
break;
}

if (child_pid == 0)
{
argv[0] = buffer;
argv[1] = NULL;

if (execve(argv[0], argv, environ) == -1)
{
perror("./shell");
exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}
}

free(input_ptr);
return (0);
}


/**
* trim_spaces - Removes leading and trailing spaces from a string
* @str: String to trim
* Return: Pointer to the trimmed string (same pointer)
*/
char *trim_spaces(char *str)
{
int start = 0, end;

if (str == NULL)
return (NULL);

while (str[start] == ' ' || str[start] == '\t')
start++;

end = strlen(str) - 1;
while (end >= start && (str[end] == ' ' || str[end] == '\t'))
end--;

str[end + 1] = '\0';
return (str + start);
}
