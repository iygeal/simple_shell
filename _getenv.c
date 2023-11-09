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

/**
 * path_list - Create a linked list of directories
 * from the given PATH variable
 * @path: A string containing a colon-separated
 * list of directories
 * Return: A pointer to the head of the
 * linked list of directories
*/

PathNode *build_path_list(char *path)
{
	PathNode *head = NULL;
	PathNode *tail = NULL;

	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		PathNode *new_node = malloc(sizeof(PathNode));

		if (new_node == NULL)
		{
			perror("Failed to allocate memory for new node");
			exit(EXIT_FAILURE);
		}

		new_node->dir = _strdup(dir);
		new_node->next = NULL;

		if (head == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}

		dir = strtok(NULL, ":");
	}
	return (head);
}

/**
 * _strchr - A function that returns a string
 * when it finds a char
 * @str: The string mixed with a delimiter
 * @j: The delimiter
 * Return: the str before the delimiter
 */

char *_strchr(const char *str, int j)
{

	while (*str != '\0')
	{
		if (*str == j)
		{
			return ((char *)str);
		}
		str++;
	}
	if (j == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}

/**
 * handle_sigint - Signal handler for SIGINT (Ctrl+c)
 * @sig: Signal number
*/

void handle_sigint(int sig)
{
	(void)sig;

	write(STDOUT_FILENO, "\n", 1);
	my_print("iyjim_shell$ ");
	fflush(stdout);
<<<<<<< HEAD
}
=======
}
>>>>>>> b13081d (simple shell implementation)
