#include "shell.h"

/**
 * split_line - splits a line into words
 * @line: The line to be split
 * Return: An array of words
 */

char **split_line(char *line)
{
  char **words = malloc(MAX_LINE * sizeof(char *));
  char *word, *word_cp;
  int index = 0, in_quotes = 0;

  if (!words)
  {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  word = strtok(line, " ");

  while (word != NULL)
  {
    if (index >= MAX_LINE)
    {
      perror("Index out of bounds");
      exit(EXIT_FAILURE);
    }

    word_cp = _strdup(word);

    if (word_cp == NULL)
    {
      perror("Memory allocation failed ");
      exit(EXIT_FAILURE);
    }

    if (word_cp[0] == '"' || (_strlen(word_cp) > 0 && word_cp[_strlen(word_cp)-1] == '"'))
    {
      if (!in_quotes && word_cp[0] == '"')
      {
        in_quotes = 1;
        memmove(word_cp, word_cp + 1, _strlen(word_cp));
      }
      else if (_strlen(word_cp) > 0 && word_cp[_strlen(word_cp) -1] == '"')
      {
        in_quotes = 0;
        word_cp[_strlen(word_cp) -1] = '\0';
      }
    }
    words[index] = (word_cp);
    index++;

    while (in_quotes && (word = strtok(NULL, " ")) != NULL)
    {
      if (index >= MAX_LINE)
      {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
      }

      word_cp = _strdup(word);

      if (word_cp == NULL)
      {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
      }

      if (_strlen(word_cp) > 0 && word_cp[_strlen(word_cp) - 1] == '"')
      {
        in_quotes = 0;
        word_cp[_strlen(word_cp) - 1] = '\0';
      }

      words[index] = word_cp;
      index++;
    }
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

  len = _strlen(line);

  if (len > 0 && line[len - 1] == '\n')
  {
    line[len - 1] = '\0';
  }

  words = split_line(line);

  for (i = 0; words[i] != NULL; i++);

  *argv_exec = malloc((i + 1) * sizeof(char *));

  if (*argv_exec == NULL)
  {
    perror("Malloc failed");
    exit(EXIT_FAILURE);
  }

  for (i = 0; words[i] != NULL; i++)
  {	
    (*argv_exec)[i] = _strdup(words[i]);

    if ((*argv_exec)[i] == NULL)
    {
      perror("Strdup failed");
      exit(EXIT_FAILURE);
    }

  }

  (*argv_exec)[i] = NULL;

  for (i = 0; i < MAX_LINE; i++)
  {
    if (words[i] != NULL)
    {
    free(words[i]);
    }
    else
    {
      break;
    }
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

      _strcpy(buffer, "Child ");

      do
      {
        temp = num % 10;
        numBuffer[digits++] = temp + '0';
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
      _strcat(buffer, numBuffer);
      _strcat(buffer, " terminated\n");

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
  path_copy = _strdup(path);

  if (command[0] == '/')
  {
    if(access(command, F_OK | X_OK) == 0)
    {
      return (_strdup(command));
    }
    else
    {
      return (NULL);
    }
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
        filepath = malloc(_strlen(dir) + _strlen(command) + 2);

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
