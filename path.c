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
	int len;

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

/**
 * search_dirs - Iterates through PATH directories to find binary
 * @path_dup: Duplicated PATH string to tokenize
 * @cmd: The command name to locate
 *
 * Return: Full path to binary if found, or NULL if not found
 */
static char *search_dirs(char *path_dup, char *cmd)
{
	char *dir, *full_path;
	struct stat st;
	int full_len;

	dir = strtok(path_dup, ":");
	while (dir != NULL)
	{
		full_len = _strlen(dir) + _strlen(cmd) + 2;
		full_path = malloc(sizeof(char) * full_len);
		if (!full_path)
			return (NULL);

		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, cmd);

		if (stat(full_path, &st) == 0)
			return (full_path);

		free(full_path);
		dir = strtok(NULL, ":");
	}

	return (NULL);
}

/**
 * find_path - Searches PATH environment variable to locate binary
 * @cmd: The command name to locate
 *
 * Return: Full path to binary if found, or NULL if not found
 */
char *find_path(char *cmd)
{
	char *path_env, *path_dup, *res;
	struct stat st;

	if (!cmd || *cmd == '\0')
		return (NULL);

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (stat(cmd, &st) == 0)
			return (_strdup(cmd));
		return (NULL);
	}

	path_env = _getenv("PATH");
	if (!path_env || *path_env == '\0')
		return (NULL);

	path_dup = _strdup(path_env);
	if (!path_dup)
		return (NULL);

	res = search_dirs(path_dup, cmd);
	free(path_dup);

	return (res);
}
