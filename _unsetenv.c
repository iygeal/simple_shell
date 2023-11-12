#include "shell.h"
/**
 * _unsetenv - Function that unsets environment variable
 * @name: The variable name
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	if (!name)
	{
		print_err("unsetenv", 1, "Variable not found");
		return (-1);
	}
	if (unsetenv(name) != 0)
	{
		char *mut_name = strdup(name);

		if (!mut_name)
		{
			print_err("unsetenv", 2, "Memory allocation failure");
			return (-1);
		}
		print_err("unsetenv", 2, mut_name);
		free(mut_name);
		return (-1);
	}
	return (0);
}
