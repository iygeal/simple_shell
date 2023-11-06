#include "shell.h"

/**
 *_getenv - Get a copy of the value of an environment variable
 *@name: The name of the environment variable
 *Return: A new string containing the value of the environment variable
 */

char *_getenv(const char *name)
{
	char *value = getenv(name);

	if (value == NULL)
	{
		return (NULL);
	}
	return (_strdup(value));
}
