#include "main.h"

/**
 * tokenize_input - Splits a command string into arguments
 * @line: Raw command line string
 *
 * Return: Dynamically allocated array of token pointers (NULL-terminated),
 *         or NULL on failure
 */
char **tokenize_input(char *line)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);

	token = strtok(line, " \t\r\n");
	while (token != NULL && i < 63)
	{
		args[i] = token;
		token = strtok(NULL, " \t\r\n");
		i++;
	}
	args[i] = NULL;

	return (args);
}
