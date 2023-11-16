#include "shell.h"

/**
 * generate_child_message - Generates a termination
 * message for a child process.
 * @buffer: The buffer to store the message
 * @child_num: The child process number
 */

void generate_child_message(char *buffer, int child_num)
{
	char numBuffer[10];
	char tmp;
	int temp, digits = 0, j = 0, num = child_num;

	_strcpy(buffer, "Child ");

	do {
		temp = num % 10;
		numBuffer[digits++] = temp + '0';
		num /= 10;
	}
		while (num != 0);

	for (j = 0; j < digits / 2; j++)
	{
		tmp = numBuffer[j];
		numBuffer[j] = numBuffer[digits - j - 1];
		numBuffer[digits - j - 1] = tmp;
	}
	numBuffer[digits] = '\0';
	_strcat(buffer, numBuffer);
	_strcat(buffer, " terminated\n");
}

/**
 * execute_ls_command - Executes the ls -l /tmp command
 * in 5 different child processes
 * @argv_exec: The array containing the command and
 * arguments for execvp function
 */

void execute_ls_command(char **argv_exec)
{
	char buffer[100] = {0};
	pid_t pid = 0;
	int status = 0, i = 0;

	for (i = 0; i < NUM_CHILD_PROCESSES; i++)
	{
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
			generate_child_message(buffer, i + 1);
			my_print(buffer);
		}
	}
}

/**
 * handle_dir - Handles a directory in the PATH.
 * @dir: The directory to handle.
 * @command: The command to locate.
 * Return: The absolute path of the command
 * in the directory if found, otherwise NULL.
 */

char *handle_dir(char *dir, char *command)
{
	char *filepath = malloc(_strlen(dir) + _strlen(command) + 2);

	if (!filepath)
	{
		perror("Failed to allocate memory for filepath");
		exit(EXIT_FAILURE);
	}

	filepath[0] = '\0';

	_strcat(filepath, dir);
	_strcat(filepath, "/");
	_strcat(filepath, command);

	if (access(filepath, F_OK) == 0)
	return (filepath);

	free(filepath);
	return (NULL);
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

	path = getenv("PATH");
	path_copy = _strdup(path);

	if (command[0] == '/')
	{
		if (access(command, F_OK | X_OK) == 0)
		return (_strdup(command));
		else
		return (NULL);
	}
	if (!path)
	{
		perror("PATH environment variable not set");
		return ("NULL");
	}
	if (!path_copy)
	{
		perror("Failed to duplicate PATH");
		exit(EXIT_FAILURE);
	}
	dir = strtok(path_copy, ":");

	while (dir)
	{
		filepath = handle_dir(dir, command);

		if (filepath)
		{
			free(path_copy);
			return (filepath);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

