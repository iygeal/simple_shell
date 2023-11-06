#include "shell.h"

/**
 * main - main function
 * @argc: The count of the command line arguments
 * @argv: The array of the command line arguments
 * Return: 0 if successful
 */

int main(int argc, char **argv)
{
	int i;
	char *line = NULL;
	size_t len = 0;
	char **argv_exec = NULL;

	(void)argc;

	print_arguments(argv);

	while (1)
	{
		my_print("iyjim_shell$ ");
		if (getline(&line, &len, stdin) != -1)
		{
			process_line(line, &argv_exec);
			fork_and_execute(argv_exec);
		}
		else
		{
			perror("getline failed");
			exit(0);
		}
	}
	if (argv_exec != NULL)
	{
		for (i = 0; argv_exec[i] != NULL; i++)
		{
			free(argv_exec[i]);
		}
		free(argv_exec);
	}
	free(line);

	return (0);
}
