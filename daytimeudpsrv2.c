/*
 * =============================================================================
 *
 *       Filename:  daytimeudpsrv2.c
 *
 *    Description:  UDP time get server program that protocol independent.
 *		    figure 11-19, page 266.
 *
 *        Version:  1.0
 *        Created:  03/15/2015 01:12:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <time.h>

int main(int argc, char *argv[])
{
	int	sockfd;
	ssize_t	n;
	char	buff[MAXLINE];
	time_t	ticks;
	socklen_t len;
	struct	sockaddr_storage cliaddr;

	if (argc == 2)
		sockfd = udp_server(NULL, argv[1], NULL);
	else if (argc == 3)
		sockfd = udp_server(argv[1], argv[2], NULL);
	else 
		err_quit("usage: daytimeudpsrv2 [<host>] <service or port>");
	for ( ; ; ) {
		len = sizeof(cliaddr);
		if ((n = recvfrom(sockfd, buff, MAXLINE, 0, (SA *)&cliaddr,
				&len)) < 0)
			err_sys("recvfrom error");
		printf("datagram from %s\n", sock_ntop((SA *)&cliaddr, len));

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if (sendto(sockfd, buff, strlen(buff), 0, (SA *)&cliaddr,
				len) < 0)
			err_sys("sendto error");
	}
}
