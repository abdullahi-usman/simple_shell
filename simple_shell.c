#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "main.h"

/**
 * set_mem - set memory at buf
 * @mem: the memory
 * @size: the size of memory
 * @cmd: the cmd to fill in
 */
void set_mem(void **mem, size_t size, void *cmd)
{
	size_t i;

	if (mem != NULL)
	{

		for (i = 0; i < size; i++)
		{
			*(mem + i) = cmd;
		}
	}
}

/**
 * split - split string
 * @line: the line
 * Return: the return string
 */
char **split(char *line)
{
	int c = -1;
	char *tok, **cmd_line = NULL;

	if (strlen(line) > 0)
	{
		cmd_line = (char **)malloc(sizeof(char *));
		tok = line;

		do {
			c++;
			tok = strtok(tok, " ");

			if (tok != NULL)
			{
				tok[strlen(tok) - 1] = '\0';
				*(cmd_line + c) = tok;
			}
			tok = NULL;
		} while (*(cmd_line + c) != NULL);

		*(cmd_line + c) = NULL;
		return (cmd_line);
	}

	return (NULL);
}

/**
 * check_exit_and_env - check exit and env and print
 * @command_line: the command
 * @env: the env
 */
void check_exit_and_env(char *command_line, char **env)
{
	if (strcmp(command_line, "exit") == 0)
		exit(0);

	if (strcmp(command_line, "env") == 0)
	{
		while (env++ != NULL)
			puts(*env);
	}
}

/**
 * super_simple_shell - a simple shell
 * @env: env
 * Return: status
 */
int super_simple_shell(char **env)
{
	size_t cmd_size = 10, input_size = sizeof(char) * 1024;
	char *input = (char *)malloc(input_size), **command_line = NULL;
	pid_t ch_pid = -1;
	int ch_pid_status = 0;

	set_mem((void **)command_line, cmd_size, NULL);
	while (printf("$ ") && getline(&input, &input_size, stdin) != -1)
	{
		command_line = split(input);
		if ((*command_line) == NULL || strlen(*command_line) <= 0)
		{
			perror("Command input is empty");
			continue;
		}

		check_exit_and_env(*command_line, env);
		ch_pid = fork();

		if (ch_pid != 0)
		{
			errno = -1;
			if (execve(find_command(*command_line), command_line, NULL) == -1)
			{
				puts(*command_line);
				perror("Failed to execute command");
			}
		}
		else
		{
			waitpid(ch_pid, &ch_pid_status, 0);
		}
	}

	if (input != NULL)
		free(input);

	if (command_line != NULL)
		free(command_line);

	return (0);
}
