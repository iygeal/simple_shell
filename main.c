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
	char line[MAX_LINE];
	char **argv_exec = NULL;

	(void)argc;

	print_arguments(argv);

	while (1)
	{
		my_print("iyjim_shell$ ");
		if (fgets(line, MAX_LINE, stdin) != NULL)
		{
			process_line(line, &argv_exec);
			fork_and_execute(argv_exec);
		}
		else
		{
			perror("fgets failed");
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
	return (0);
}
