#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
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
char **create_argv_exec(char **words);
void free_words(char **words);
void print_arguments(char **argv);
char **split_line(char *line);
char *handle_quotes(char *word_cp, int *in_quotes);
void copy_word_and_handle_quotes(char *word, int *in_quotes,
int *index, char **words);
void execute_ls_command(char **argv_exec);
void generate_child_message(char *buffer, int child_num);
char *find_command(char *command);
char *handle_dir(char *dir, char *command);
void handle_sigint(int sig);
PathNode *build_path_list(char *path);
void free_argv_exec(char ***argv_exec);
void print_and_process_line(char **line, char ***argv_exec);
void read_and_process_file(char *argv[]);
void process_buffer(char *buffer, int bytes_read);
void change_dir(char **argv_exec);
void change_and_update_pwd(char *dir_to_go);
void handle_exit(char **argv_exec);
void handle_which(char **argv_exec);
void check_path_and_execute(char *path, char *command);
void handle_other_commands(char **argv_exec, int *childExitStatus);
void ex_chd(char *cmd_path, char **argv_exec, int *childExitStatus);
int set_environment_path(void);
char *get_path(void);
void process_standard_input(char **line, char ***argv_exec);
void process_input(int argc, char **line, char ***argv_exec, char **argv);


char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);
char *_strchr(const char *str, int j);
void free_path_list(PathNode *head);
void free_strdup(char *str);
void free_malloc(void *ptr);
#endif
