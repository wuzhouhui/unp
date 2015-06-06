/*
 * =============================================================================
 *
 *       Filename:  dg_echo.c
 *
 *    Description:  called by udpserv01.c
 *
 *        Version:  1.0
 *        Created:  03/09/2015 10:31:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	int	n;
	socklen_t len;
	char	mesg[MAXLINE];

	for ( ; ; ) {
		len = clilen;
		if ((n = recvfrom(sockfd, mesg, MAXLINE, 0, 
						pcliaddr,
						&len)) < 0)
			err_sys("dg_echo: recvfrom error");
		if (n != sendto(sockfd, mesg, n, 0, pcliaddr, len))
			err_ret("dg_echo: sendto error");
	}
}
