/*
 * =============================================================================
 *
 *       Filename:  start_connect.c
 *
 *    Description:  start nonblocking connect(). figure 16-17, page 358.
 *
 *        Version:  1.0
 *        Created:  03/26/2015 06:39:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "web.h"

void start_connect(struct file *fptr)
{
	int	fd, flags, n;
	struct addrinfo *ai;

	if ((ai = host_serv(fptr->f_host, SERV, 0, SOCK_STREAM)) == NULL)
		err_sys("start_connect: host_serv error");
	if ((fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) < 0)
		err_sys("start_connect: socket error");
	fptr->f_fd = fd;
	printf("start_connect for %s, fd %d\n", fptr->f_name, fd);

	if ((flags = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("start_connect: fcntl with F_GETFL error");
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
		err_sys("start_connect: fcntl with F_SETFL error");

	if ((n = connect(fd, ai->ai_addr, ai->ai_addrlen)) < 0) {
		if (errno != EINPROGRESS)
			err_sys("start_connect: connect error");
		fptr->f_flags = F_CONNECTIONG;
		FD_SET(fd, &rset);
		FD_SET(fd, &wset);
		if (fd > maxfd)
			maxfd = fd;
	} else if (n >= 0)
		write_get_cmd(fptr);
}
