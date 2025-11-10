#include "shell.h"
/**
* trim_whitespace - Removes leading and trailing whitespace
* @str: String to trim
*
* Return: Pointer to trimmed string
*/
char *trim_whitespace(char *str)
{
char *end;

while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
str++;

if (*str == '\0')
return (str);

end = str + strlen(str) - 1;
while (end > str && (*end == ' ' || *end == '\t'
|| *end == '\n' || *end == '\r'))
end--;

*(end + 1) = '\0';

return (str);
}
/**
* parse_command - Parses command line into arguments
* @line: Command line to parse
* @argv: Array to store argument pointers
*
* Return: Number of arguments parsed
*/
int parse_command(char *line, char **argv)
{
int argc = 0;
char *token;

token = strtok(line, " \t\n\r\"'");
while (token != NULL && argc < MAX_ARGS - 1)
{
argv[argc++] = token;
token = strtok(NULL, " \t\n\r\"'");
}
argv[argc] = NULL;

return (argc);
}
