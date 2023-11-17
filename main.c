#include "shell.h"

/**
 * process_buffer - process the buffer read from file
 * @buffer: the buffer read from file
 * @bytes_read: number of bytes read from file
 */

void process_buffer(char *buffer, int bytes_read)
{
	int start_index = 0, end_index = 0;
	char *line = NULL, **argv_exec = NULL, *temp;
	size_t len;
	int childExitStatus;

	while (start_index < bytes_read)
	{
		temp = _strchr(buffer + start_index, '\n');
		end_index = (temp != NULL) ? (temp - buffer) : bytes_read;

		end_index = (end_index < start_index) ? start_index : end_index;
		buffer[end_index] = '\0';

		len = end_index - start_index + 1;
		line = malloc(len);
		if (line == NULL)
		{
			perror("malloc: line");
			exit(EXIT_FAILURE);
		}

		_strcpy(line, buffer + start_index);
		process_line(line, &argv_exec);
		fork_and_execute(argv_exec, &childExitStatus);

		free_argv_exec(&argv_exec);
		free(line);
		line = NULL;
		start_index = end_index + 1;
	}
}

/**
 * read_and_process_file - read from file and process each line
 * @argv: array of command line arguments
 * Return: void
 */

void read_and_process_file(char *argv[])
{
	int fd;
	char buffer[1024];
	int bytes_read;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open: argv[1]");
		exit(EXIT_FAILURE);
	}

	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		process_buffer(buffer, bytes_read);
	}

	if (bytes_read == -1)
	{
		perror("read: file");
		exit(EXIT_FAILURE);
	}

	close(fd);
}

/**
 * print_and_process_line - print prompt and process input line
 * @line: pointer to input line
 * @argv_exec: pointer to array of arguments
 * Return: void
 */

void print_and_process_line(char **line, char ***argv_exec)
{
	int childExitStatus;
	size_t len = 0;

	my_print("iyjim_shell$ ");
	if (getline(line, &len, stdin) != -1)
	{
		process_line(*line, argv_exec);
		fork_and_execute(*argv_exec, &childExitStatus);
	}
	else
	{
		if (feof(stdin))
		{
			my_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline: stdin");
		}
	}

	free_argv_exec(argv_exec);
	free(*line);
	*line = NULL;
}


/**
 * main - main function
 * @argc: The count of the command line arguments
 * @argv: Array of the command line arguments
 * Return: 0 if successful
 */


int main(int argc, char *argv[])
{
	char *line = NULL;
	char **argv_exec = NULL;
	char *path;
	PathNode *path_list, *tmp;
	int c = 0;

	(void)argc;
	print_arguments(argv);
	signal(SIGINT, handle_sigint);
	set_environment_path();
	path = get_path();
	path_list = build_path_list(path);
	free(path);
	process_input(argc, &line, &argv_exec, argv);

	while (argv_exec[c] != NULL)
	{
		free(argv_exec[c]);
		c++;
	}
	while (path_list != NULL)
	{
		tmp = path_list;
		path_list = path_list->next;
		free(tmp->dir);
		free(tmp);
	}
	return (0);
}

