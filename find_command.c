#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * find_command - find where the command is located
 * @command: maybe relative command
 * Return: the composited command
 */
char *find_command(char *command)
{
	char *token, *path = NULL;

	if (index(command, '/') != NULL)
	{
		return (command);
	}

	path = getenv("PATH");

	if (path != NULL)
	{
		while ((path = strtok(path, ":")) != NULL)
		{

			token = (char *)malloc(sizeof(char) * (strlen(command) + strlen(path)) + 2);

			strcat(token, path);
			strcat(token, "/");
			strcat(token, command);
			strcat(token, "\0");

			if (access(token, F_OK) != -1)
			{
				return (token);
			}
			path = NULL;
		}
	}

	return (command);
}
