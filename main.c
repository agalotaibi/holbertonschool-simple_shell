#include "shell.h"
/**
 * handle_command - Processes and executes the trimmed command.
 * @trimmed: The whitespace-trimmed command line.
 * @buffer: The original getline buffer (for exiting).
 * @interactive: Flag for interactive mode.
 *
 * Return: status of the command.
 */
static int handle_command(char *trimmed, char *buffer, int interactive)
{
	char *cmd_copy;
	int status = 0;

	if (trimmed[0] == '\0')
		return (0);

	cmd_copy = strdup(trimmed);
	if (cmd_copy == NULL)
		return (-1);

	if (strcmp(cmd_copy, "env") == 0)
	{
		print_env();
		free(cmd_copy);
		return (0);
	}
	if (strcmp(cmd_copy, "exit") == 0)
	{
		free(cmd_copy);
		free(buffer);
		exit(0);
	}
	status = execute_command(cmd_copy);
	free(cmd_copy);

	if (!interactive && status != 0)
	{
		free(buffer);
		exit(status);
	}
	return (status);
}

/**
 * _write_prompt - Writes the prompt or newline to stdout.
 * @interactive: Flag for interactive mode.
 * @eof: Flag for end-of-file (getline read -1).
 */
static void _write_prompt(int interactive, int eof)
{
	char *prompt = "#cisfun$ ";
	char *newline = "\n";

	if (interactive)
	{
		if (eof)
			write(STDOUT_FILENO, newline, 1);
		else
			write(STDOUT_FILENO, prompt, 8);
	}
}
/**
 * main - Entry point for the simple shell
 * @ac: Argument count (unused)
 * @av: Argument vector (unused)
 *
 * Return: Exit status of the last command, or 0.
 */
int main(int ac, char **av)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t nread;
	int interactive, status = 0;

	(void)ac;
	(void)av;

	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		_write_prompt(interactive, 0);

		nread = getline(&buffer, &bufsize, stdin);
		if (nread == -1)
		{
			_write_prompt(interactive, 1);
			break;
		}

		if (nread > 0 && buffer[nread - 1] == '\n')
			buffer[nread - 1] = '\0';

		status = handle_command(trim_whitespace(buffer), buffer, interactive);
	}

	free(buffer);
	return (status);
}
