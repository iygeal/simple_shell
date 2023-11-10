#include "shell.h"
/**
 * _setenv - Function that add/modifies an environment variable
 * @name: The environment variable
 * @value: Value to set the variable to
 * Return: 0
 */
int _setenv(char *name, const char *value)
{
	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "setenv: Variable not found\n");
		return (-1);
	}
	if (setenv(name, value, 1) != 0)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}
