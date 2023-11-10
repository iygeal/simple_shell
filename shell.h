#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>


#define MAX_LINE 1024
#define NUM_CHILD_PROCESSES 5
extern char **environ;

/**
 * struct PathNode - Represents a node in a linked
 * list of directories
 * @dir: A string representing the directory path
 * @next: A pointer to the next node in the linked list
*/
typedef struct PathNode
{
	char *dir;
	struct PathNode *next;
} PathNode;

int main(int argc, char *argv[]);
void my_print(const char *msg);
void fork_and_execute(char **argv_exec, int *childExitStatus);
void process_line(char *line, char ***argv_exec);
void print_arguments(char **argv);
char **split_line(char *line);
void execute_ls_command(char **argv_exec);
char *find_command(char *command);
char *_getenv(const char *name);
void handle_sigint(int sig);
PathNode *build_path_list(char *path);

char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);
char *_strchr(const char *str, int j);
int _setenv(char *name, const char *value);
#endif
