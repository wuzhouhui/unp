/*
 * =============================================================================
 *
 *       Filename:  udpservselect01.c
 *
 *    Description:  echo server using select to process TCP and UDP.
 *
 *        Version:  1.0
 *        Created:  03/10/2015 10:46:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

static void sig_chld(int);

int main(int argc, char *argv[])
{
	int	listenfd, connfd, udpfd, nready, maxfdp1;
	char	mesg[MAXLINE];
	pid_t	pid;
	fd_set	rset;
	ssize_t	n;
	socklen_t len;
	const int on = 1;
	struct sockaddr_in cliaddr, servaddr;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error with SOCK_STREAM");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		err_sys("setsockopt error");
	if (bind(listenfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error for TCP");

	if (listen(listenfd, LISTENQ) < 0)
		err_sys("listen error");

	if ((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error with SOCK_DGRAM");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if (bind(udpfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error for UDP");

	if (signal(SIGCHLD, sig_chld) == SIG_ERR)
		err_sys("signal error");

	FD_ZERO(&rset);
	maxfdp1 = max(listenfd, udpfd) + 1;
	for ( ; ; ) {
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);
		if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
			/* interupted by SIGCHLD */
			if (errno == EINTR)
				continue;
			else 
				err_sys("select error");
		}

		if (FD_ISSET(listenfd, &rset)) {
			len = sizeof(cliaddr);
			if ((connfd = accept(listenfd, (SA *)&cliaddr, &len)) < 0)
				err_sys("accept error");

			if ((pid = fork()) == 0) {
				close(listenfd);
				str_echo(connfd);
				exit(0);
			} else if (pid < 0)
				err_sys("fork error");
			close(connfd);
		}

		if (FD_ISSET(udpfd, &rset)) {
			len = sizeof(cliaddr);
			if ((n = recvfrom(udpfd, mesg, MAXLINE, 0, (SA *)&cliaddr, &len)) < 0)
				err_sys("recvfrom error");
			if (n != sendto(udpfd, mesg, n, 0, (SA *)&cliaddr, len))
				err_sys("sendto error");
		}
	}
}

static void sig_chld(int signo)
{
	printf("an child process terminated");
}
