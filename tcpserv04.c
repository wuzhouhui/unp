/*
 * =============================================================================
 *
 *       Filename:  tcpserv04.c
 *
 *    Description:  final version that handle accept returns EINTR.
 *
 *        Version:  4.0
 *        Created:  2015年03月04日 07时22分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int main(int argc, char **argv)
{
	int	listenfd, connfd;
	pid_t	pid;
	socklen_t clilen;
	struct	sockaddr_in cliaddr, servaddr;
	void	sig_chld(int);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	 = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port	 = htons(SERV_PORT);

	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);
	Signal(SIGCHLD, sig_chld); /* must call waitpid() */

	for (;;) {
		clilen = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (SA *)&cliaddr, &clilen)) < 0) {
			if (errno == EINTR)
				continue;
			else 
				err_sys("accept error");
		}

		if ((pid = fork()) == 0) { /* child */
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}

		/* parent */
		Close(connfd);
	}
}
