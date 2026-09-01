#include "main.h"

/**
 * print - Prints a string to stdout
 * @s: String to print
 *
 * Return: void
 */
void print(const char *s)
{
	if (s)
		write(STDOUT_FILENO, s, _strlen(s));
}

/**
 * print_prompt - Displays the shell prompt in interactive mode
 *
 * Return: void
 */
void print_prompt(void)
{
	print("$ ");
}

/**
 * read_input - Reads a line of input from standard input
 *
 * Return: Pointer to the allocated string line, or NULL on EOF/error
 */
char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
