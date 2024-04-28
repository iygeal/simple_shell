#include "shell.h"

/**
 * check_path_and_execute - Checks if a command is in the PATH and executes it
 * @path: The PATH string
 * @command: The command to check for
 *
 * Return: void
 */

void check_path_and_execute(char *path, char *command)
{
	char *dir = strtok(path, ":");
	char *filepath = NULL;
	char *msg = NULL;

	while (dir != NULL)
	{
		filepath = malloc(_strlen(dir) + _strlen(command) + 2);
		if (filepath == NULL)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		_strcpy(filepath, dir);
		_strcat(filepath, "/");
		_strcat(filepath, command);

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
		msg = malloc(_strlen(command) + 12);
		_strcpy(msg, command);
		_strcat(msg, " not found");
		my_print(msg);

		free(msg);
	}
}


/**
 * handle_other_commands - Handles other commands
 * @argv_exec: The array containing the command
 * @childExitStatus: Pointer to an int to store the exit status
 *
 * Return: void
 */
void handle_other_commands(char **argv_exec, int *childExitStatus)
{
	char *msg = NULL, *msg_fmt = NULL, *cmd_path = NULL;

	cmd_path = find_command(argv_exec[0]);
	if (!cmd_path)
	{
		msg_fmt = ": Command not found\n";
		msg = malloc(_strlen(argv_exec[0]) + _strlen(msg_fmt) + 1);
		if (!msg)
		{
			perror("malloc error");
			exit(EXIT_FAILURE);
		}

		_strcpy(msg, argv_exec[0]);
		_strcat(msg, msg_fmt);

		my_print(msg);
		free(msg);
		return;
	}

	ex_chd(cmd_path, argv_exec, childExitStatus);
	free(cmd_path);
}

/**
 * ex_chd - Executes a child process
 * @cmd_path: The path of the command to execute
 * @argv_exec: The array containing the command
 * @childExitStatus: Pointer to an int to store the exit status
 *
 * Return: void
 */
void ex_chd(char *cmd_path, char **argv_exec, int *childExitStatus)
{
	int status = 0;
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Error forking child");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, argv_exec, environ) == -1)
		{
			perror(argv_exec[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("Error waiting for child process");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			*childExitStatus = WEXITSTATUS(status);
		}
	}
}

/**
 * process_line - Process a line read from stdin.
 * @line: The line read from stdin.
 * @argv_exec: The array to be used for execve function.
 * Return: Nothing.
 */

void process_line(char *line, char ***argv_exec)
{
	char **words = NULL;
	size_t len;

	len = _strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
	printf("Error Check_two\n");
	words = split_line(line);
	printf("Check Error_three\n");
	*argv_exec = create_argv_exec(words);
	printf("Check Error_four\n");
	free(words);
	printf("Check_5\n");
}
