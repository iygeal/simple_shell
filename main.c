#include "shell.h"

/**
 * main - main function
 * @argc: The count of the command line arguments
 * @argv: The array of the command line arguments
 * Return: 0 if successful
 */

int main(int argc, char *argv[])
{
	int fd;
	char *line = NULL;
	size_t len = 0;
	char **argv_exec = NULL;
	int childExitStatus = 0;
	char buffer[1024];
	char *temp, *path;
	int start_index = 0, end_index = 0, bytes_read;
	PathNode *path_list, *tmp;

	(void)argc;

	print_arguments(argv);

	signal(SIGINT, handle_sigint);

	if (_setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin") == -1)
	{
		print_err("setenv", 1, "PATH");
		exit(EXIT_FAILURE);
	}

	path = _strdup(_getenv("PATH"));

	if (path == NULL)
	{
		print_err("strdup", 1, "PATH");
		exit(EXIT_FAILURE);
	}

	path_list = build_path_list(path);
	free(path);

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			my_print("iyjim_shell$ ");
			if (getline(&line, &len, stdin) != -1)
			{
			process_line(line, &argv_exec);
			fork_and_execute(argv_exec, &childExitStatus);
			}
			else
			{
				print_err("getline", 1, "stdin");
			}

			free_argv_exec(&argv_exec);

			free(line);
			line = NULL;
		}
	}
	else
	{
		fd = open(argv[1], O_RDONLY);

		if (fd == -1)
		{
			print_err("open", 1, argv[1]);
			exit(EXIT_FAILURE);
		}
		while((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytes_read] = '\0';

			while(start_index < bytes_read)
			{
				temp = _strchr(buffer + start_index, '\n');

				if(temp != NULL)
					end_index = temp - buffer;
				else
					end_index = bytes_read;

				if (end_index < start_index)
					end_index = start_index;					

				buffer[end_index] = '\0';

				len = end_index - start_index + 1;
				line = malloc(len);

				if (line == NULL)
				{
					print_err("malloc", 1, "line");
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
		if (bytes_read == -1)
		{
			print_err("read", 1, "file");
			exit(EXIT_FAILURE);
		}

		close(fd);

	}

	free_argv_exec(&argv_exec);

	while (path_list != NULL)
	{
		tmp = path_list;
		path_list = path_list->next;
		free(tmp->dir);
		free(tmp);
	}
	return (0);
}
