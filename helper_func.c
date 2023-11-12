#include "shell.h"

/**
 * free_argv_exec - Free allocated memory
 * @argv_exec: Double pointer to be freed
 */

void free_argv_exec(char ***argv_exec)
{
	int i;

	if (*argv_exec != NULL)
	{
		for (i = 0; (*argv_exec)[i] != NULL; i++)
			free((*argv_exec)[i]);
		free(*argv_exec);
		*argv_exec = NULL;
	}
}
