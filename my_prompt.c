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
 * split_line - splits a line into words
 * @line: The line to be split
 * Return: An array of words
 */

char **split_line(char *line)
{
	char **words = malloc(MAX_LINE * sizeof(char *));
	char *word;
	int index = 0;

	if (!words)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	word = strtok(line, " ");
	while (word != NULL)
	{
		words[index] = strdup(word);
		if (!words[index])
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		index++;
		word = strtok(NULL, " ");
	}
	words[index] = NULL;

	return (words);
}

/**
 * process_line - process a line read from stdin
 * @line: The line read from stdin
 * @argv_exec: The array to be used for execve function
 * Return: Void
 */
void process_line(char *line, char ***argv_exec)
{
	char **words = NULL;
	int i = 0;
	size_t len;

	len = strlen(line);

	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}

	words = split_line(line);

	for (i = 0; words[i] != NULL; i++);

	*argv_exec = malloc((i + 1) * sizeof(char *));

	if (*argv_exec == NULL)
	{
		perror("process_line malloc failed");
		exit(EXIT_FAILURE);
	}

	for (i = 0; words[i] != NULL; i++)
	{	
		(*argv_exec)[i] = strdup(words[i]);

		if ((*argv_exec)[i] == NULL)
		{
			perror("process_line strdup failed");
			exit(EXIT_FAILURE);
		}

	}

	(*argv_exec)[i] = NULL;

	for (i = 0; words[i] != NULL; i++)
	{
		free(words[i]);
	}
	free(words);
}

/**
 * execute_ls_command - Executes the ls -l /tmp command
 * in 5 different child processes
 * @argv_exec: The array containing the command and
 * arguments for execvp function
*/

void execute_ls_command(char **argv_exec)
{
	pid_t pid = 0;
	int status = 0, i = 0;

	for (i = 0; i < NUM_CHILD_PROCESSES; i++)
	{
		char numBuffer[10];
		char buffer[100] = {0};
		int temp, digits = 0, j = 0;
		int num = i + 1;

		pid = fork();
		if (pid < 0)
		{
			perror("Error forking child");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(argv_exec[0], argv_exec, environ);
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);

			strcpy(buffer, "Child ");

			do
			{
				temp = num % 10;
				numBuffer[digits++] = temp + 0;
				num /= 10;
			}
			while (num != 0);

			for (j = 0; j < digits / 2; j++)
			{
				char tmp = numBuffer[j];
				numBuffer[j] = numBuffer[digits - j - 1];
				numBuffer[digits - j - 1] = tmp;
			}
			numBuffer[digits] = '\0';
			strcat(buffer, numBuffer);
			strcat(buffer, " terminated\n");

			my_print(buffer);
		}
	}
}

/**
 * find_command - Locates a command in the system's PATH
 * @command: The command to locate
 * Return: The absolute path of the command or NULL if not found
 */

char *find_command(char *command)
{
	char *dir = NULL;
    char *filepath = NULL;
	char *path = NULL;
    char *path_copy = NULL;
    
	path = _getenv("PATH");
    path_copy = strdup(path);
    
	if (!path)
	{
		perror("Error: PATH environment variable not set\n");

		return ("NULL");
	}

    if (!path_copy)
    {
        perror("find_command: Failed to duplicate PATH");
        exit(EXIT_FAILURE);
    }

    dir = strtok(path_copy, ":");

    while (dir)
    {
        filepath = malloc(strlen(dir) + strlen(command) + 2);

        if (!filepath)
        {
            perror("find_command: Failed to allocate memory for filepath");
            exit(EXIT_FAILURE);
        }
		filepath[0] = '\0';

		strcat(filepath, dir);
		strcat(filepath, "/");
		strcat(filepath, command);

        if (access(filepath, F_OK) == 0)
        {
            free(path_copy);
            return (filepath);
        }

        free(filepath);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

/**
 * fork_and_execute - create a child process and execute a command
 * @argv_exec: The array containing the command
 * and arguments for execve
 */

void fork_and_execute(char **argv_exec)
{
	int i = 0, status = 0;
	char *msg = NULL;
	char *msg_fmt = NULL;
	char *cmd_path = NULL;
	pid_t pid = 0;

	if (strcmp(argv_exec[0], "_which") == 0)
	{
		char *path = NULL;

		path = strdup(_getenv("PATH"));

		if (path == NULL)
		{
			perror("fork_execute strdup failed");
			exit(EXIT_FAILURE);
		}

		for (i = 1; argv_exec[i] != NULL; i++)
		{
			char *dir = strtok(path, ":");
			char *filepath = NULL;

			while (dir != NULL)
			{
				filepath = malloc(strlen(dir) + strlen(argv_exec[i]) + 2);

				if (filepath == NULL)
				{
					perror("fork_and_exec malloc failed");
					exit(EXIT_FAILURE);
				}
				strcpy(filepath, dir);
				strcat(filepath, "/");
				strcat(filepath, argv_exec[i]);

				if (access(filepath, F_OK) == 0)
				{
					my_print(filepath);
					free(filepath);

					break;
				}
				free(filepath);

				dir = strtok(NULL, ":");
			}
			if (dir == NULL)
			{
				msg = malloc(strlen(argv_exec[1]) + 12);
				strcpy(msg, argv_exec[1]);
				strcat(msg, " not found");
				my_print(msg);
				
				free(msg);
			}
			free(path);

			path = strdup(_getenv("PATH"));

			if (path == NULL)
			{
				perror("fork_and_execute strdup failed");
				exit(EXIT_FAILURE);
			}

		}

	}
	else
	{
		cmd_path = find_command(argv_exec[0]);

		if (!cmd_path)
		{
			msg_fmt = ": Command not found\n";
			msg = malloc(strlen(argv_exec[0] + strlen(msg_fmt) + 1));

			if (!msg)
			{
				perror("malloc error");
				exit(EXIT_FAILURE);
			}

			strcpy(msg, argv_exec[0]);
			strcat(msg, msg_fmt);

			my_print(msg);

			free(msg);
			exit(EXIT_FAILURE);
		}

		pid = fork();

		if (pid < 0)
		{
			perror("Error forking child");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(cmd_path, argv_exec, environ) < 0)
			{
				perror(argv_exec[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
		free(cmd_path);
	}
	for (i = 0; argv_exec[i] != NULL; i++)
	{
		free(argv_exec[i]);
	}
	free(argv_exec);

}
