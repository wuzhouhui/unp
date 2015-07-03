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
#include <sys/socket.h>

void str_echo(int);

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
			/* exercise 7.3 requested */
			struct linger linger;
			linger.l_onoff	= 1;
			linger.l_linger	= 0;
			if (setsockopt(connfd, SOL_SOCKET, SO_LINGER,
						&linger, sizeof(linger)))
				err_sys("setsockopt error");
			exit(0);
		}

		/* parent */
		Close(connfd);
	}
}
/*
 * =============================================================================
 *
 *       Filename:  str_echo.c
 *
 *    Description:  str_echo function.
 *
 *        Version:  1.0
 *        Created:  03/03/2015 11:03:54 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void str_echo(int sockfd)
{
	ssize_t	n;
	char	buf[MAXLINE];

again:
	while ((n = read(sockfd, buf, sizeof(buf))) > 0)
		if (write(sockfd, buf, n) < 0)
			err_sys("write error");
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("str_echo: read error");
}
