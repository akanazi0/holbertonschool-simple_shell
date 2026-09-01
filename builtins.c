#include "main.h"

/**
 * handle_builtin - Checks and executes shell built-in commands
 * @args: Array of argument strings
 * @line: Input buffer to free on exit
 * @last_status: Exit status from previous command execution
 * @prog: Program name for error reporting
 * @count: Line count for error reporting
 *
 * Return: 1 if handled, 0 if not a builtin, 2 on invalid exit arg
 */
int handle_builtin(char **args, char *line,
		   int last_status, char *prog, int count)
{
	int exit_val = 0;
	int i = 0;

	if (!args || !args[0])
		return (0);

	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
		{
			exit_val = _atoi(args[1]);
			if (exit_val < 0)
			{
				fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
					prog, count, args[1]);
				return (2);
			}
			free(args);
			free(line);
			exit(exit_val);
		}
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
