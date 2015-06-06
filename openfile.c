/*
 * =============================================================================
 *
 *       Filename:  openfile.c
 *
 *    Description:  open a file and return it's descriptor.
 *
 *        Version:  1.0
 *        Created:  03/21/2015 04:35:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int main(int argc, char **argv)
{
	int	fd;

	if (argc != 4)
		err_quit("openfile <sockfd#> <filename> <mode>");
	if ((fd = open(argv[2], atoi(argv[3]))) < 0)
		exit((errno > 0) ? errno : 255);
	if (write_fd(atoi(argv[1]), "", 1, fd) < 0)
		exit((errno > 0) ? errno : 255);
	exit(0);
}
