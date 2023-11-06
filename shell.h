#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define NUM_CHILD_PROCESSES 5
extern char **environ;

void my_print(const char *msg);
int _putchar(char c);
void fork_and_execute(char **argv_exec);
void process_line(char *line, char ***argv_exec);
void print_arguments(char **argv);
char **split_line(char *line);
void execute_ls_command(char **argv_exec);
char *find_command(char *command);
char *_getenv(const char *name);

#endif /* SHELL_ */
