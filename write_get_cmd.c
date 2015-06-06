/*
 * =============================================================================
 *
 *       Filename:  write_get_cmd.c
 *
 *    Description:  send a HTTP GET command to server, figure 16-18, page
 *			359.
 *
 *        Version:  1.0
 *        Created:  03/26/2015 06:15:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "web.h"

void write_get_cmd(struct file *fptr)
{
	int	n;
	char	line[MAXLINE];

	n = snprintf(line, sizeof(line), GET_CMD, fptr->f_name);
	Writen(fptr->f_fd, line, n);
	printf("wrote %d bytes for %s\n", n, fptr->f_name);
	fptr->f_flags = F_READING;
	FD_SET(fptr->f_fd, &rset);
	if (fptr->f_fd > maxfd)
		maxfd = fptr->f_fd;
}
