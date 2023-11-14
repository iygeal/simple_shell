#include "shell.h"

/**
 * fork_and_execute - create a child process and execute a command
 * @argv_exec: The array containing the command
 * and arguments for execve
 * @childExitStatus: Pointer to an int to store the exit status
 *
 * Return: void
 */
void fork_and_execute(char **argv_exec, int *childExitStatus)
{
	if (_strcmp(argv_exec[0], "exit") == 0 &&
	_strlen(argv_exec[0]) == _strlen("exit"))
	{
		handle_exit(argv_exec);
	}
	else if (_strcmp(argv_exec[0], "_which") == 0)
	{
		handle_which(argv_exec);
	}
	else if (_strcmp(argv_exec[0], "cd") == 0)
	{
		change_dir(argv_exec);
	}
	else
	{
		handle_other_commands(argv_exec, childExitStatus);
	}
}

/**
 * change_dir - changes the current directory of the process
 * @argv_exec: The array containing the command
 * and arguments for execve
 */
void change_dir(char **argv_exec)
{
	char *dir_to_go = NULL;

	if (argv_exec[1] == NULL || _strcmp(argv_exec[1], "~") == 0)
	{
		dir_to_go = getenv("HOME");
	}
	else if (_strcmp(argv_exec[1], "-") == 0)
	{
		dir_to_go = getenv("OLDPWD");
		printf("%s\n", dir_to_go);
	}
	else
	{
		dir_to_go = argv_exec[1];
	}

	if (dir_to_go == NULL)
	{
		my_print("cd: No such file or directory");
		return;
	}

	change_and_update_pwd(dir_to_go);
}


/**
 * change_and_update_pwd - changes the current directory and updates PWD
 * @dir_to_go: The directory to go
 */

void change_and_update_pwd(char *dir_to_go)
{
	char oldpwd[1024];
	char newpwd[1024];

	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
	{
		perror("Error getting the current working directory");
		exit(EXIT_FAILURE);
	}

	if (chdir(dir_to_go) != 0)
	{
		perror("Error changing the current directory");
		exit(EXIT_FAILURE);
	}

		if (setenv("OLDPWD", oldpwd, 1) != 0)
	{
		perror("Error setting OLDPWD environment variable");
		exit(EXIT_FAILURE);
	}

	if (getcwd(newpwd, sizeof(newpwd)) == NULL)
	{
		perror("Error getting the current working directory");
		exit(EXIT_FAILURE);
	}

	if (setenv("PWD", newpwd, 1) != 0)
	{
		perror("Error setting PWD environment variable");
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_exit - Handles the 'exit' command
 * @argv_exec: The array containing the command
 *
 * Return: void
 */

void handle_exit(char **argv_exec)
{
	int exit_status = 0;

	if (argv_exec[1] != NULL)
	{
		exit_status = atoi(argv_exec[1]);
		if (exit_status < 0 || exit_status > 255)
		{
			my_print("Exit status out of range. Must be between 0 and 255.\n");
			return;
		}
	}

	exit(exit_status);
}

/**
 * handle_which - Handles the '_which' command
 * @argv_exec: The array containing the command
 *
 * Return: void
 */

void handle_which(char **argv_exec)
{
	int i;
	char *path = NULL;

	path = _strdup(_getenv("PATH"));
	if (path == NULL)
	{
		perror("_strdup failed");
		exit(EXIT_FAILURE);
	}

	for (i = 1; argv_exec[i] != NULL; i++)
	{
		check_path_and_execute(path, argv_exec[i]);
	}

	free(path);
}
