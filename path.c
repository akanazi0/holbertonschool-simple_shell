#include "main.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: Name of the environment variable to look up
 *
 * Return: Pointer to the variable's value string, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	int len = 0;

	if (!name || !environ)
		return (NULL);

	len = _strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);
		i++;
	}

	return (NULL);
}
