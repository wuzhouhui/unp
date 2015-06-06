/*
 * =============================================================================
 *
 *       Filename:  tcpserv01.c
 *
 *    Description:  TCP echo server.
 *
 *        Version:  1.0
 *        Created:  03/03/2015 10:56:55 AM
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
	int	listenfd, connfd;
	pid_t	pid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	 = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port	 = htons(SERV_PORT);
	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	for (;;) {
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);
		if ((pid = fork()) == 0) { /* child */
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}

		/* parent */
		Close(connfd);
	}
}
