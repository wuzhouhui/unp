/*
 * =============================================================================
 *
 *       Filename:  tcpservpoll01.c
 *
 *    Description:  TCP server using poll.
 *
 *        Version:  1.0
 *        Created:  03/05/2015 07:05:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <limits.h>

#ifndef OPEN_MAX
#define OPEN_MAX 1024
#endif

int main(int argc, char **argv)
{
	int	i, maxi, listenfd, connfd, sockfd;
	int	nready;
	ssize_t	n;
	char	buf[MAXLINE];
	socklen_t clilen;
	struct	pollfd client[OPEN_MAX];
	struct	sockaddr_in cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	 = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port	 = htons(SERV_PORT);

	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	client[0].fd	 = listenfd;
	client[0].events = POLLRDNORM;
	for (i = 1; i < OPEN_MAX; i++)
		client[i].fd = -1;
	maxi = 0;

	for ( ; ; ) {
		nready = Poll(client, maxi + 1, INFTIM);

		if (client[0].revents & POLLRDNORM) { /* new client connection */
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);

			for (i = 1; i < OPEN_MAX; i++)
				if (client[i].fd < 0) {
					client[i].fd = connfd;
					break;
				}

			if (i == OPEN_MAX)
				err_quit("too many clients");

			client[i].events = POLLRDNORM;
			maxi = i > maxi ? i : maxi;
			if (--nready <= 0)
				continue;
		}

		for (i = 1; i <= maxi; i++) {
			if ((sockfd = client[i].fd) < 0)
				continue;
			if (client[i].revents & (POLLRDNORM | POLLERR)) {
				if ((n = read(sockfd, buf, MAXLINE)) < 0) {
					if (errno == ECONNRESET) {
						/* connection reset by client */
						Close(sockfd);
						client[i].fd = -1;
					} else {
						err_sys("read error");
					}
				} else if (n == 0) {
					/* connection reset by client */
					Close(sockfd);
					client[i].fd = -1;
				} else {
					Writen(sockfd, buf, n);
				}

				if (--nready <= 0)
					break;
			}
		}
	}
}
