#include "main.h"

/**
 * handle_builtin - Checks and executes shell built-in commands
 * @args: Array of argument strings
 * @line: Input buffer to free on exit
 *
 * Return: 1 if a built-in was executed, 0 otherwise
 */
int handle_builtin(char **args, char *line)
{
	if (!args || !args[0])
		return (0);

	if (_strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(0);
	}

	return (0);
}
