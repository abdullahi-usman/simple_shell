#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * main - entry point
 * @argc: the argc
 * @argv: the argv
 * @env: the environment
 *
 * Return: status;
 */
int main(int argc, char **argv, char **env)
{

	pid_t pid;
	int status;

	if (argc > 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Cannot fork process");
		}
		else if (pid == 0)
		{
			(*argv + 1)[strlen(*argv) - 1] = '\0';
			*(argv + argc) = NULL;
			puts(*argv);
			execve(find_command(*(argv + 1)), argv + 1, env == NULL ? environ : env);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}
	else
	{
		return (super_simple_shell(env == NULL ? environ : env));
	}

	return (0);
}
