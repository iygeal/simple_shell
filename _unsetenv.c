#include "shell.h"
/**
 * _unsetenv - Function that unsets environment variable
 * @name: The variable name
 * Return: 0 on success, -1 on failure
 */

int _unsetenv(const char *name)
{
	char *mut_name;

	if (!name)
	{
		perror("Variable not found");
		return (-1);
	}
	if (unsetenv(name) != 0)
	{
		mut_name = strdup(name);

		if (!mut_name)
		{
			perror("Memory allocation failure");
			return (-1);
		}
		perror(mut_name);
		free(mut_name);
		return (-1);
	}
	return (0);
}
