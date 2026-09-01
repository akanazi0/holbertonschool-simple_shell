#include "main.h"

/**
 * _strcat - Concatenates two strings
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: Pointer to dest
 */
char *_strcat(char *dest, const char *src)
{
	int dest_len = 0;
	int i = 0;

	if (!dest || !src)
		return (dest);

	while (dest[dest_len])
		dest_len++;

	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * _atoi - Converts a string to an integer
 * @s: Input string
 *
 * Return: Converted integer, or -1 if invalid characters are present
 */
int _atoi(const char *s)
{
	int i = 0;
	unsigned int num = 0;

	if (!s)
		return (-1);

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		num = (num * 10) + (s[i] - '0');
		i++;
	}

	return ((int)num);
}
