/*
 * =============================================================================
 *
 *       Filename:  daytimeudpcli1.c
 *
 *    Description:  time get client program using udp_client() and UDP.
 *		    figure 11-16, page 263.
 *
 *        Version:  1.0
 *        Created:  03/15/2015 12:38:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int main(int argc, char *argv[])
{
	int	sockfd, n;
	char	recvline[MAXLINE + 1]; /* plus 1 for terminator */
	socklen_t salen;
	struct	sockaddr *sa;

	if (argc != 3)
		err_quit("usage: daytimeudpcli1 <hostname/IPaddress>"
			 " <service/port#>");

	sockfd = udp_client(argv[1], argv[2], (SA **)&sa, &salen);
	printf("sending to %s\n", sock_ntop_host(sa, salen));
	if (sendto(sockfd, " ", 1, 0, sa, salen) < 0)
		err_sys("sendto error");
	if ((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0)
		err_sys("recvfrom error");
	recvline[n] = 0;
	fputs(recvline, stdout);

	exit(0);
}
