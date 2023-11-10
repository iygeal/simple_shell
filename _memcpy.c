#include "shell.h"
/**
 * _memcpy - Function that copies memory into string
 * @src: Source string
 * @dest: Destination string
 * @n: Number of bytes to copy
 * Return: dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
return (dest);
}
