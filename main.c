#include "main.h"

/**
 * print - function print
 * @s: string to be printed
 * Return: void
 */
void print(const char *s)
{
	write(STDOUT_FILENO, s, strlen(s));
}

/**
 * print_prompt - function prints $
 * 
 * Return: void
 */
void print_prompt(void)
{
	print("$ ");
}

/**
 * get_line_from_user - read line from stdin
 * 
 * Return: pointer, or NULL on EOF/error
 */
char *read_input(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;

	characters_read = getline(&line, &bufsize, stdin);
	if (characters_read == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * exec_cmd - function excute command
 * @cmd: command 
 * Return: void
 */
void exec_cmd(char *cmd, char *prog_name, int count)
{
	pid_t child_pid;
	int status;
	char *args[64];
	char *token;
	int i = 0;

	token = strtok(cmd, " \t\r\n");
	while (token != NULL && i < 63)
	{
		args[i] = token;
		token = strtok(NULL, " \t\r\n");
		i++;
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	else if (child_pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, count, args[0]);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - function runs the program 
 * 
 * Return: 0
 */
int main(int ac, char **av)
{
	char *line = NULL;
	int line_count = 0;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();

		line = read_input();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line_count++;
		exec_cmd(line, av[0], line_count);

		free(line);
	}

	return (0);
}
