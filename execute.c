#include "shell.h"
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
fprintf(stderr, "%s: No such file or directory\n", argv[0]);
return (127);
}
pid = fork();
if (pid == -1)
{
perror("fork");
free(command_path);
return (-1);
}
else if (pid == 0)
{
if (execve(command_path, argv, environ) == -1)
{
perror(argv[0]);
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
