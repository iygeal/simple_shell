#include "shell.h"

/**
 * set_environment_path - Set the environment path
 * Return: 0 on success, exit on failure
 */

int set_environment_path(void)
{
	if (_setenv("PATH",
	"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin") == -1)
	{
		perror("setenv: PATH");
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * get_path - Get the path
 * Return: Pointer to the path string
 */

char *get_path(void)
{
	char *path = _strdup(_getenv("PATH"));

	if (path == NULL)
	{
		perror("strdup: PATH");
		exit(EXIT_FAILURE);
	}
	return (path);
}

/**
 * process_standard_input - Process the standard input
 * @line: Pointer to the line string
 * @argv_exec: Pointer to the argv_exec
 */

void process_standard_input(char **line, char ***argv_exec)
{
	size_t len = 0;
	int childExitStatus;

	while (getline(line, &len, stdin) != -1)
	{
		process_line(*line, argv_exec);
		fork_and_execute(*argv_exec, &childExitStatus);
		free_argv_exec(argv_exec);
		free(*line);
		*line = NULL;
	}
}

/**
 * process_input - Process the input
 * @argc: The count of command line arguments
 * @line: Pointer to the line string
 * @argv_exec: Pointer to the argv_exec
 * @argv: Array of command line arguments
 */

void process_input(int argc, char **line, char ***argv_exec, char **argv)
{
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			print_and_process_line(line, argv_exec);
		}
	}
	else
	{
		if (argc >= 2)
		{
			read_and_process_file(argv);
		}
		else
		{
			process_standard_input(line, argv_exec);
		}
	}
}
