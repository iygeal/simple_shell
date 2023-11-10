#include "shell.h"
/**
 * _setenv - Function that add or modifies environment variables
 * @name: Name of the variable
 * @value: The value to set it the variable to
 * @overwrite: Flag to determine whether to overwrite if name already exists
 * Return: 0 on success; -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int i, newEnvSize;
	cha **envPtr = environ, **newEnvArray;

	if (name == NULL || value == NULL || _strchr(name, '=') != NULL)
		return (-1);
	while (*envPtr != NULL)
	{
		if (_strncmp(*envPtr, name, _strlen(name)) == 0)
			break;
		envPtr++;
	}
	if (*envPtr != NULL)
	{
		if (overwrite)
		{
			free(*envPtr);
			*envPtr = malloc(_strlen(name) + _strlen(value) + 2);
			if (*envPtr == NULL)
				return (-1);
			sprintf(*envPtr, "%s=%s", name, value);
		}
	} else
	{
		newEnvSize = (envPtr - environ) + 2;
		newEnvArray = malloc(newEnvSize * sizeof(char *));
		if (newEnvArray == NULL)
			return (-1);
		_memcpy(newEnvArray, environ, (envPtr - environ) * sizeof(char *));
		newEnvArray[newEnvSize - 2] = malloc(_strlen(name) + _strlen(value) + 2);
		if (newEnvArray[newEnvSize - 2] == NULL)
		{
			free(newEnvArray);
			return (-1);
		}
		sprintf(newEnvArray[newEnvSize - 2], "%s=%s", name, value);
		newEnvArray[newEnvSize - 1] = NULL;
		free(environ);
		environ = newEnvArray;
	}
	return (0);
}
