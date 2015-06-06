/*
 * =============================================================================
 *
 *       Filename:  unixstrserv01.c
 *
 *    Description:  echo server program using unix domain stream socket.
 *		    figure 15-3, page 328.
 *
 *        Version:  1.0
 *        Created:  03/19/2015 10:38:29 PM
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
	int	listenfd, connfd;
	pid_t	childpid;
	socklen_t clilen;
	struct	sockaddr_un cliaddr, servaddr;

	if ((listenfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	unlink(UNIXSTR_PATH);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	if (bind(listenfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");
	if (listen(listenfd, LISTENQ) < 0)
		err_sys("listen error");
	if (signal(SIGCHLD, sig_chld) == SIG_ERR)
		err_sys("signal error");

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (SA *)&cliaddr, &clilen)) < 0) {
			if (errno = EINTR) /* interrupted by SIGCHLD */
				continue;
			else 
				err_sys("accept error");
		}

		if ((childpid = fork()) < 0) {
			err_sys("fork error");
		} else if (childpid == 0) {
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
}

static void sig_chld(int signo)
{
	return;
}
