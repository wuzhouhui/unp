/*
 * =============================================================================
 *
 *       Filename:  daytimetcpserv2.c
 *
 *    Description:  time get server program using tcp_listen, it is protocol
 *		    independent. figure 11-14, page 261.
 *
 *        Version:  1.0
 *        Created:  03/15/2015 11:12:57 AM
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
	int	listenfd, connfd;
	socklen_t len, addrlen;
	char	buff[MAXLINE];
	time_t	ticks;
	struct	sockaddr_storage cliaddr;

	if (argc == 2)
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	else if (argc == 3)
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
	else 
		err_quit("usage: daytimetcpserv2 [<host>] <service or port>");
	for ( ; ; ) {
		len = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (SA *)&cliaddr, &len)) < 0)
			err_sys("accept error");
		printf("connection from %s\n", sock_ntop((SA *)&cliaddr, len));

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if (write(connfd, buff, strlen(buff)) < 0)
			err_sys("write error");

		close(connfd);
	}
}
