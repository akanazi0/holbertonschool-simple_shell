#include "main.h"

/**
 * exec_cmd - Executes parsed arguments by resolving PATH and forking
 * @args: Array of argument strings
 * @prog_name: Name of the shell executable (for error reporting)
 * @count: Current line count for error reporting
 *
 * Return: Status code of the execution
 */
int exec_cmd(char **args, char *prog_name, int count)
{
	char *actual_cmd;
	pid_t child_pid;
	int status;

	actual_cmd = find_path(args[0]);
	if (!actual_cmd)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, count, args[0]);
		return (127);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(actual_cmd);
		return (1);
	}
	else if (child_pid == 0)
	{
		if (execve(actual_cmd, args, environ) == -1)
		{
			perror(prog_name);
			free(actual_cmd);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free(actual_cmd);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (0);
}
