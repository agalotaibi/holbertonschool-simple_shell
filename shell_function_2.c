#include "shell.h"
/**
* path_and_check - Builds a full path and checks if it's executable.
* @token: the directory from the PATH
* @command: The command to append.
*
* Return: The full path if it exists and is executable, NULL otherwise.
*/
static char *path_and_check(char *token, char *command)
{
char *file_path;
int command_length, directory_length;
struct stat buffer;

directory_length = strlen(token);
command_length = strlen(command);

file_path = malloc(directory_length + command_length + 2);
if (file_path == NULL)
{
perror("malloc");
return (NULL);
}
strcpy(file_path, token);
strcat(file_path, "/");
strcat(file_path, command);

if (stat(file_path, &buffer) == 0)
return (file_path);

free(file_path);
return (NULL);
}

/**
* get_location - Finds the full path of an executable command.
* @command: The command to locate.
*
* Return: The full path of the command, or NULL if not found.
*/
char *get_location(char *command)
{
char *path, *path_copy, *path_token, *file_path = NULL;
struct stat buffer;

if (strchr(command, '/') != NULL)
{
if (stat(command, &buffer) == 0)
return (strdup(command));
else
return (NULL);
}
path = _getenv("PATH");
if (path)
{
path_copy = strdup(path);
if (path_copy == NULL)
return (NULL);

path_token = strtok(path_copy, ":");
while (path_token != NULL)
{
file_path = path_and_check(path_token, command);
if (file_path)
{
free(path_copy);
return (file_path);
}
path_token = strtok(NULL, ":");
}
free(path_copy);
}
return (NULL);
}
