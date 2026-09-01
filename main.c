#include "main.h"

/**
 * main - Entry point for the simple shell
 * @ac: Argument count (unused)
 * @av: Argument vector (contains program name)
 *
 * Return: Status of the last executed command
 */
int main(int ac, char **av)
{
	char *line = NULL;
	char **args = NULL;
	int line_count = 0;
	int last_status = 0;
	int builtin_ret = 0;

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
		args = tokenize_input(line);
		if (args != NULL && args[0] != NULL)
		{
			builtin_ret = handle_builtin(args, line, last_status, av[0], line_count);
			if (builtin_ret == 0)
				last_status = exec_cmd(args, av[0], line_count);
			else if (builtin_ret == 2)
				last_status = 2;
			else
				last_status = 0;
		}

		free(args);
		free(line);
	}

	return (last_status);
}
