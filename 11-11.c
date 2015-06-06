/*
 * =============================================================================
 *
 *       Filename:  11-11.c
 *
 *    Description:  time get program client using tcp_connect(user defined).
 *
 *        Version:  1.0
 *        Created:  03/15/2015 10:44:25 AM
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
	socklen_t len;
	struct	sockaddr_storage ss;

	if (argc != 3)
		err_quit("usage: daytimetcpcli <hostname/IPaddress>"
			 " <service/port#>");

	sockfd = Tcp_connect(argv[1], argv[2]);
	
	len = sizeof(ss);
	Getpeername(sockfd, (SA *)&ss, &len);
	printf("connect to %s\n", Sock_ntop_host((SA *)&ss, len));

	while ((n = Read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		Fputs(recvline, stdout);
	}
	exit(0);
}
