#include "shell.h"
/**
 * _write_err - Writes a string to standard error.
 * @str: The string to write.
 */
static void _write_err(char *str)
{
	if (!str)
		return;
	write(STDERR_FILENO, str, strlen(str));
}
/**
 * _write_num_err - Writes an integer to standard error.
 * @n: The integer to write.
 */
static void _write_num_err(int n)
{
	char c;

	if (n / 10)
		_write_num_err(n / 10);
	c = (n % 10) + '0';
	write(STDERR_FILENO, &c, 1);
}
/**
 * fork_and_exec - Handles the fork, exec, and wait logic.
 * @cmd_path: The full path to the command.
 * @argv: The arguments for the command.
 *
 * Return: The exit status of the command.
 */
static int fork_and_exec(char *cmd_path, char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		_write_err("fork error\n");
		free(cmd_path);
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(cmd_path, argv, environ) == -1)
		{
			_write_err(argv[0]);
			_write_err(": execve error\n");
			free(cmd_path);
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (0);
}
/**
 * execute_command - Executes a command
 * @line: The command line to execute
 * Return: Exit status of command
 */
int execute_command(char *line)
{
	int argc;
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
		_write_err("./hsh: ");
		_write_num_err(cmd_count);
		_write_err(": ");
		_write_err(argv[0]);
		_write_err(": not found\n");

		cmd_count++;
		return (127);
	}
	cmd_count++;
	return (fork_and_exec(command_path, argv));
}
