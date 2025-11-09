#include "shell.h"

char **parse_input(char *input)
{
char **args;
char *token;
int i = 0;
int bufsize = 64;

args = malloc(sizeof(char *) * bufsize);
if (!args)
{
perror("malloc");
exit(EXIT_FAILURE);
}

token = strtok(input, " \t");
while (token != NULL)
{
args[i++] = token;
token = strtok(NULL, " \t");
}
args[i] = NULL;

return args;
}

/**
 * _strncmp - Compares two strings up to n bytes.
 * @s1: The first string.
 * @s2: The second string.
 * @n: The number of bytes to compare.
 *
 * Return: 0 if s1 and s2 are equal, otherwise non-zero.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable (e.g., "PATH").
 *
 * Return: A pointer to the value of the variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t name_len;
	
	if (name == NULL || environ == NULL)
		return (NULL);
	name_len = strlen(name);
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], name, name_len) == 0 &&
				environ[i][name_len] == '=')
			return (environ[i] + name_len + 1);
		i++;
	}
	return (NULL);
}
