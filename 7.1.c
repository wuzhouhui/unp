/*
 * =============================================================================
 *
 *       Filename:  7.1.c
 *
 *    Description:  exercise 7.1: get the default buffer size of TCP and 
 *		    UDP.
 *
 *        Version:  1.0
 *        Created:  03/08/2015 08:15:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

static void pr_opt(int, int, const char *);

int main(void)
{
	int	fd;

	/*
	 * TCP
	 */
	if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		err_sys("socket error for TCP");
	pr_opt(fd, SO_RCVBUF, "TCP");
	pr_opt(fd, SO_SNDBUF, "TCP");
	close(fd);

	/*
	 * UDP 
	 */
	if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		err_sys("socket error for UDP");
	pr_opt(fd, SO_RCVBUF, "UDP");
	pr_opt(fd, SO_SNDBUF, "UDP");
	close(fd);

	exit(0);
}

static void pr_opt(int fd, int optname, const char *proto)
{
	int	val;
	socklen_t len = sizeof(val);

	switch (optname) {
	case SO_RCVBUF:
		if (getsockopt(fd, SOL_SOCKET, SO_RCVBUF,
					&val, &len) < 0)
			err_sys("getsockopt error");
		printf("%s SO_RCVBUF: %d Bytes\n", proto, val);
		break;

	case SO_SNDBUF:
		if (getsockopt(fd, SOL_SOCKET, SO_SNDBUF,
					&val, &len) < 0)
			err_sys("getsockopt error");
		printf("%s SO_SNDBUF: %d Bytes\n", proto, val);
		break;

	default:
		printf("UNKNOWN case\n");
	}
}
