/*
 * =============================================================================
 *
 *       Filename:  dgecholoop2.c
 *
 *    Description:  function dg_echo that expand socket recv buffer,
 *		    figure 8-22, page 203.
 *
 *        Version:  1.0
 *        Created:  03/10/2015 10:19:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

static void recvfrom_int(int);
static int count;

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	int	n;
	socklen_t len;
	char	mesg[MAXLINE];

	if (signal(SIGINT, recvfrom_int) == SIG_ERR)
		err_sys("dg_echo: signal error");

	n = 220 * 1024;
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n)) < 0)
		err_sys("dg_echo: setsockopt error");
	for ( ; ; ) {
		len = clilen;
		if (recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len) < 0)
			err_sys("dg_echo: recvfrom error");
		count++;
	}
}

static void recvfrom_int(int signo)
{
	printf("\nreceived %d datagrams\n", count);
	exit(0);
}
