/*
 * =============================================================================
 *
 *       Filename:  mycat.c
 *
 *    Description:  mycat: copy a file to stdout.
 *
 *        Version:  1.0
 *        Created:  03/21/2015 03:42:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

extern int my_open(const char *, int);

int main(int argc, char *argv[])
{
	int	fd, n;
	char	buff[BUFFSIZE];

	if (argc != 2)
		err_quit("usage: mycat <pathname>");
	if ((fd = my_open(argv[1], O_RDONLY)) < 0)
		err_sys("cannot open %s", argv[1]);
	while ((n = read(fd, buff, BUFFSIZE)) > 0)
		if (n != write(STDOUT_FILENO, buff, n))
			err_sys("write error");
	exit(0);
}
