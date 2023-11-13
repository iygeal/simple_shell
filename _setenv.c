#include "shell.h"
/**
 * _setenv - Add/modifies an environment variable.
 * @name: The environment variable.
 * @value: Value to set the variable to.
 * Return: 0 on success, -1 on failure.
 */

int _setenv(char *name, const char *value)
{
	if (name == NULL || value == NULL)
	{
		perror("Variable not found");
		return (-1);
	}

	if (setenv(name, value, 1) != 0)
	{
		perror(name);
		return (-1);
	}

	return (0);
}
