#include "main.h"

/**
 * main - Entry point for the simple shell
 * @ac: Argument count (unused)
 * @av: Argument vector (contains program name)
 *
 * Return: Always 0 (Success)
 */
int main(int ac, char **av)
{
	char *line = NULL;
	char **args = NULL;
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
		args = tokenize_input(line);
		if (args != NULL && args[0] != NULL)
		{
			if (!handle_builtin(args, line))
				exec_cmd(args, av[0], line_count);
		}

		free(args);
		free(line);
	}

	return (0);
}
