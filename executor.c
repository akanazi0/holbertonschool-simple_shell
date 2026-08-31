#include "main.h"

/**
 * exec_cmd - Executes parsed arguments in a child process
 * @args: Array of argument strings
 * @prog_name: Name of the shell executable (for error reporting)
 * @count: Current line count for error reporting
 *
 * Return: void
 */
void exec_cmd(char **args, char *prog_name, int count)
{
	pid_t child_pid;
	int status;

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
