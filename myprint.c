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


/**
 * print_err - Print formatted error message
 * @prg: Program name
 * @cnt: Command count
 * @cmd: User command
 */

void print_err(char *prg, int cnt, char *cmd)
{
	int len_p, len_c;
	char d;

	len_p = _strlen(prg);
	len_c = _strlen(cmd);
	write(2, prg, len_p);
	write(2, ": ", 2);
	if (cnt < 10)
	{
		d = cnt + '0';
		write(2, &d, 1);
	}
	else if (cnt > 9 && cnt < 100)
	{
		d = (cnt / 10) + '0';
		write(2, &d, 1);
		d = (cnt % 10) + '0';
		write(2, &d, 1);
	}
	write(2, ": ", 2);
	write(2, cmd, len_c);
	write(2, ": ", 2);
	write(2, "not found\n", 10);
}
