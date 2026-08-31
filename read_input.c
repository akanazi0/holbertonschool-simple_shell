#include "main.h"

/**
 * print - Writes a string to standard output
 * @s: The string to be printed
 *
 * Return: void
 */
void print(const char *s)
{
	write(STDOUT_FILENO, s, strlen(s));
}

/**
 * print_prompt - Prints the shell prompt symbol
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
