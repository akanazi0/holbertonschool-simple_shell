#include "main.h"

/**
 * handle_builtin - Checks and executes shell built-in commands
 * @args: Array of argument strings
 * @line: Input buffer to free on exit
 * @last_status: Exit status from previous command execution
 *
 * Return: 1 if a built-in was executed, 0 otherwise
 */
int handle_builtin(char **args, char *line, int last_status)
{
	int i = 0;

	if (!args || !args[0])
		return (0);

	if (_strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(last_status);
	}

	if (_strcmp(args[0], "env") == 0)
	{
		while (environ && environ[i])
		{
			print(environ[i]);
			print("\n");
			i++;
		}
		return (1);
	}

	return (0);
}
