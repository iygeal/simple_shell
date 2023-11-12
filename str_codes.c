#include "shell.h"
/**
 * _strdup - Function that returns a pointer to newly allocated space in memory
 * @str: A string
 * Return: Returns new string or NULL
 */
char *_strdup(const char *str)
{
	int i;
	int n = 0;
	char *str2;

	if (str == NULL)
	{
		return (NULL);
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		n++;
	}
	str2 = malloc(n * sizeof(char) + 1);

	if (str2 == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < n; i++)
	{
		str2[i] = str[i];
	}
	str2[i] = '\0';

return (str2);

}

/**
 * _strcat - String Concatenator
 * @dest: Destination string
 * @src: Source string
 * Return: destlen
 */
char *_strcat(char *dest, char *src)
{
	char *destlen = dest;

	if (dest == NULL || src == NULL)
		return (NULL);

	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return (destlen);
}

/**
 * _strlen - Calculates string length
 * @s: String whose length is to be calclulated
 * Return: _strlen
 */
int _strlen(const char *s)
{
	int i;
	int length = 0;

	for (i = 0; s[i] != '\0'; i++)
		length++;
	return (length);
}


/**
 * char *_strcpy - This function copies the string pointed to by src
 * @dest: copy to
 * @src: copy from
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0;

	while (*(src + l) != '\0')
	{
		l++;
	}

	dest[l] = '\0';

	return (dest);
}

/**
 * _strcmp - Function which compares strings
 * @s1: First String
 * @s2: Second string
 * Return: 0, +ve or -ve
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0 ; s1[i] != '\0' && s2[i] != '\0' ; i++)
	{
		if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	}
	return (0);
}
