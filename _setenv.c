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
		print_err("setenv", 1, "Variable not found");
		return (-1);
	}

	if (setenv(name, value, 1) != 0)
	{
		print_err("setenv", 2, name);
		return (-1);
	}

	return (0);
}
