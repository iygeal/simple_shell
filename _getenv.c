#include "shell.h"

/**
 * print_arguments - print command line arguments
 * @argv: The array of the command line arguments
 * Return: Void
 */

void print_arguments(char **argv)
{
	argv++;

	while (*argv)
	{
		my_print(*argv);
		my_print("\n");
		argv++;
	}
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

		new_node->dir = strdup(dir);

		if (new_node->dir == NULL)
		{
			perror("Failed to duplicate directory string");
			free(new_node);
			exit(EXIT_FAILURE);
		}

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
}

