/*
 * =============================================================================
 *
 *       Filename:  tcpservselect01.c
 *
 *    Description:  TCP server using single process and select(): circle.
 *
 *        Version:  1.0
 *        Created:  03/05/2015 06:09:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <sys/resource.h>

int main(int argc, char **argv)
{
	int	i, maxfd, listenfd, connfd, sockfd, maxi;
	int	nready, *client, fd_size;
	ssize_t	n;
	fd_set	rset, allset;
	char	buf[MAXLINE];
	socklen_t clilen;
	struct	sockaddr_in cliaddr, servaddr;
	struct rlimit limit;

	if (getrlimit(RLIMIT_NOFILE, &limit))
		err_sys("getrlimit error");
	if (limit.rlim_cur == RLIM_INFINITY)
		fd_size = 2048;
	else 
		fd_size = limit.rlim_cur;
	if (!(client = malloc(fd_size * sizeof(int))))
		err_sys("malloc error");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	 = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port	 = htons(SERV_PORT);

	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	maxfd	= listenfd;	/* initialize */
	maxi	= -1;		/* index into client[] array */
	for (i = 0; i < fd_size; i++)
		client[i] = -1;	/* -1 indicates available entry */
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	for ( ; ; ) {
		rset	= allset;	/* structure assignment */
		nready	= Select(maxfd + 1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(listenfd, &rset)) { /* new client connection */
			clilen	= sizeof(cliaddr);
			connfd	= Accept(listenfd, (SA *)&cliaddr, &clilen);

			for (i = 0; i < fd_size; i++)
				if (client[i] < 0) {
					client[i] = connfd;
					break;
				}
			if (i == fd_size)
				err_quit("too many clients");

			FD_SET(connfd, &allset); /* add new descriptor to set */
			maxfd	= connfd > maxfd ? connfd : maxfd;
			maxi	= i > maxi ? i : maxi;
			if (--nready <= 0)
				continue; /* no more readable descriptor */
		}

		for (i = 0; i <= maxi; i++) { /* check all clients for data */
			if ((sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset)) {
				if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
					/* connection closed by client */
					Close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				} else {
					Writen(sockfd, buf, n);
				}

				if (--nready <= 0)
					break;
			}
		}
	}
}
