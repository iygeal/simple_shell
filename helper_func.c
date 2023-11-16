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

/**
 * free_path_list - free the memory allocated for a linked list of PathNode
 * @head: pointer to the head of the linked list
 * Return: void
 */
void free_path_list(PathNode *head)
{
	PathNode *current = head;
	PathNode *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->dir);
		free(current);
		current = next;
	}
}
