#include "shell.h"

/**
 * my_print - function that uses the 'write' system call to output a string
 * to the standard output (STDOUT)
 * @msg: the string to be printed to STDOUT
*/
void my_print(const char *msg)
{
	write(STDOUT_FILENO, msg, _strlen(msg));
}
