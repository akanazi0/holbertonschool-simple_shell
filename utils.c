#include "main.h"

/**
 * _strlen - Returns the length of a string
 * @s: The string to evaluate
 *
 * Return: Length of string
 */
int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (s[len])
		len++;

	return (len);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if equal, difference between first non-matching characters
 */
int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	if (!s1 || !s2)
		return (-1);

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;

	return (s1[i] - s2[i]);
}

/**
 * _strdup - Duplicates a string in dynamically allocated memory
 * @str: String to duplicate
 *
 * Return: Pointer to duplicated string, or NULL on failure
 */
char *_strdup(const char *str)
{
	char *dup;
	int len, i;

	if (!str)
		return (NULL);

	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);

	for (i = 0; i <= len; i++)
		dup[i] = str[i];

	return (dup);
}

/**
 * _strcpy - Copies string from src to dest
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	if (!dest || !src)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
