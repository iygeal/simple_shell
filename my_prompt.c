#include "shell.h"

/**
 * handle_quotes - Handles quotes in a word
 * @word_cp: The word to handle quotes for
 * @in_quotes: Pointer to a flag indicating if we're inside quotes.
 * Return: The word with quotes handled.
 */

char *handle_quotes(char *word_cp, int *in_quotes)
{
	if (word_cp[0] == '"' || (_strlen(word_cp) > 0 &&
	word_cp[_strlen(word_cp) - 1] == '"'))
	{
		if (!(*in_quotes) && word_cp[0] == '"')
		{
			*in_quotes = 1;
			memmove(word_cp, word_cp + 1, _strlen(word_cp));
		}
		else if (_strlen(word_cp) > 0 && word_cp[_strlen(word_cp) - 1] == '"')
		{
			*in_quotes = 0;
			word_cp[_strlen(word_cp) - 1] = '\0';
		}
	}
	return (word_cp);
}

/**
 * copy_word_and_handle_quotes - Copies a word and handles quotes.
 * @word: The word to copy and handle quotes for.
 * @in_quotes: Pointer to a flag indicating if we're inside quotes.
 * @index: Pointer to the index to insert the word into the words array.
 * @words: The words array.
 */

void copy_word_and_handle_quotes(char *word, int *in_quotes,
int *index, char **words)
{
	char *word_cp;

	if (*index >= MAX_LINE)
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

	word_cp = handle_quotes(word_cp, in_quotes);
	words[*index] = word_cp;
	(*index)++;
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
	int index = 0, in_quotes = 0;

	if (!words)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	word = strtok(line, " ");

	while (word != NULL)
	{
		copy_word_and_handle_quotes(word, &in_quotes, &index, words);

		while (in_quotes && (word = strtok(NULL, " ")) != NULL)
		{
			copy_word_and_handle_quotes(word, &in_quotes, &index, words);
		}

		word = strtok(NULL, " ");
	}

	words[index] = NULL;

	return (words);
}

/**
 * create_argv_exec - Create an argv array for execve function.
 * @words: Pointer to words array
 * Return: Pointer to the argv array
 */

char **create_argv_exec(char **words)
{
	int i = 0;
	char **argv_exec;

	while (words[i] != NULL)
	i++;

	argv_exec = malloc((i + 1) * sizeof(char *));
	if (argv_exec == NULL)
	{
		perror("Malloc failed");
		exit(EXIT_FAILURE);
	}

	for (i = 0; words[i] != NULL; i++)
	{
		if (words[i][0] == '$')
		{
			char *env_value = _getenv(words[i] + 1);

			if (env_value != NULL)
			{
				free(words[i]);
				words[i] = _strdup(env_value);
				if (words[i] == NULL)
				{
					perror("Strdup failed");
					exit(EXIT_FAILURE);
				}
			}
		}
		argv_exec[i] = _strdup(words[i]);
		if (argv_exec[i] == NULL)
		{
			perror("Strdup failed");
			exit(EXIT_FAILURE);
		}
	}
	argv_exec[i] = NULL;
	return (argv_exec);
}

/**
 * free_words - Free the memory allocated for words
 * @words: Pointer to words array
 * Return: Nothing
 */

void free_words(char **words)
{
	int i;

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
