#include "shell.h"
/**
 * _strncmp - Function that compares up to n chars of two strings
 * @s1: First string
 * @s2: Second string
 * @n: Number of characters to compare in both strings
 * Return: 0 or appropriate int
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	int diff;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	for (i = 0; i < n && s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff != 0)
			return (diff);
	}
	if (s1[i] != '\0' && s2[i] == '\0' || s1[i] == '\0' && s2[i] != '\0')
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
