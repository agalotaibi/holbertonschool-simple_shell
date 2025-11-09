#include "shell.h"

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_len, directory_length;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		path_copy = strdup(path);
		if (path_copy == NULL)
		{
			perror("strdup");
			return (NULL);
		}
	/*Get the length of the command*/
		command_len = strlen(command);
	/*Break down the path_copy variable into individual tokens*/
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_len + directory_length + 2);
			if (file_path == NULL)
			{
				perror("malloc");
				free(path_copy);
				return (NULL);
			}
		/* to build the path for the command*/
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
			return (strdup(command));
	}
	return (NULL);
}
