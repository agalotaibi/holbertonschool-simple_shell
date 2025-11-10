#include "shell.h"
/**
* execute_command - Executes a command
* @line: The command line to execute
* Return: Exit status of command
**/
int execute_command(char *line)
{
pid_t pid;
int status, argc;
char *argv[MAX_ARGS], *command_path = NULL;
static int cmd_count = 1;
if (line == NULL || line[0] == '\0')
return (0);
argc = parse_command(line, argv);
if (argc == 0 || check_builtin(argv))
return (0);
command_path = get_location(argv[0]);
if (command_path == NULL)
{
fprintf(stderr, "./hsh: %d: %s: not found\n", cmd_count, argv[0]);
cmd_count++;
return (127);
}
pid = fork();
if (pid == -1)
{
perror("fork");
free(command_path);
return (-1);
}
if (pid == 0)
{
if (execve(command_path, argv, environ) == -1)
{
perror(argv[0]);
free(command_path);
exit(127);
}
}
waitpid(pid, &status, 0);
free(command_path);
cmd_count++;
if (WIFEXITED(status))
return (WEXITSTATUS(status));
return (0);
}
