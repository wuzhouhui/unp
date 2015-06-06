/*
 * =============================================================================
 *
 *       Filename:  dgecholoop.c
 *
 *    Description:  function dg_echo that count the number of datagram
 *		    received. figure 8-20, page 201
 *
 *        Version:  1.0
 *        Created:  03/10/2015 10:06:40 PM
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
	socklen_t len;
	char	mesg[MAXLINE];

	if (signal(SIGINT, recvfrom_int) == SIG_ERR)
		err_sys("dg_echo: signal error");

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
