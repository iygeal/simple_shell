#include "shell.h"
/**
 * _unsetenv - Function that unsets environment variable
 * @name: The variable name
 * Return: 0
 */
int _unsetenv(const char *name)
{
	if (!name)
	{
		fprintf(stderr, "unsetenv: Variable not found\n");
		return (-1);
	}
	if (unsetenv(name) != 0)
	{
		perror("unsetenv now");
		return (-1);
	}
	return (0);
}

