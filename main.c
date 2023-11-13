#include "shell.h"

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
        perror("getline: stdin");
    }

    free_argv_exec(argv_exec);
    free(*line);
    *line = NULL;
}

/**
 * read_and_process_file - read from file and process each line
 * @argv: array of command line arguments
 * Return: void
 */

void read_and_process_file(char *argv[])
{
    int fd;
    int childExitStatus;
    char *line = NULL;
    char buffer[1024];
    char **argv_exec = NULL;
    char *temp;
    int start_index = 0;
    int end_index = 0;
    int bytes_read;
    size_t len;

    fd = open(argv[1], O_RDONLY);

    if (fd == -1)
    {
        perror("open: argv[1]");
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0';

        while (start_index < bytes_read)
        {
            temp = _strchr(buffer + start_index, '\n');

            if (temp != NULL)
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

    if (bytes_read == -1)
    {
        perror("read: file");
        exit(EXIT_FAILURE);
    }

    close(fd);

    free_argv_exec(&argv_exec);
}

/**
 * main - main function
 * @argc: The count of the command line arguments
 * @argv: The array of the command line arguments
 * Return: 0 if successful
 */

int main(int argc, char *argv[])
{
    char *line = NULL;
    char **argv_exec = NULL;
    char *path;
    PathNode *path_list, *tmp;
    size_t len = 0;
    int childExitStatus;

    (void)argc;
    print_arguments(argv);

    signal(SIGINT, handle_sigint);

    if (_setenv("PATH",
        "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin") == -1)
    {
        perror("setenv: PATH");
        exit(EXIT_FAILURE);
    }

    path = _strdup(_getenv("PATH"));

    if (path == NULL)
    {
        perror("strdup: PATH");
        exit(EXIT_FAILURE);
    }

    path_list = build_path_list(path);
    free(path);

    if (isatty(STDIN_FILENO))
    {
        while (1)
        {
            print_and_process_line(&line, &argv_exec);
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
            while (getline(&line, &len, stdin) != -1)
            {
                process_line(line, &argv_exec);
                fork_and_execute(argv_exec, &childExitStatus);
                free_argv_exec(&argv_exec);
                free(line);
                line = NULL;
            }
        }
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
