#include "shell.h"

/**
* check_builtin - Checks if command is a built-in and executes it
* @argv: Array of command arguments
*
* Return: 1 if built-in was executed, 0 if not a built-in
*/
int check_builtin(char **argv)
{
if (argv[0] == NULL)
return (0);

if (strcmp(argv[0], "exit") == 0)
{
exit(0);
}

return (0);
}
/**
 * print_env - print env
 *
 * Return: void
 **/
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
