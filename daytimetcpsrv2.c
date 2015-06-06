/*
 * =============================================================================
 *
 *       Filename:  daytimetcpsrv2.c
 *
 *    Description:  protocol independent time get server program, run as 
 *		    daemonized process. figure 13-5, page 292.
 *
 *        Version:  1.0
 *        Created:  03/16/2015 02:27:52 PM
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
	socklen_t addrlen, len;
	struct	sockaddr *cliaddr;
	char	buff[MAXLINE];
	time_t	ticks;

	if (argc < 2 || argc > 3)
		err_quit("uage: daytimetcpsrv2 [<host>] <service or port>");
	daemon_init(argv[0], 0);
	if (argc == 2 )
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	else 
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
	if (listenfd < 0)
		err_sys("tcp_listen error");
	if ((cliaddr = malloc(addrlen)) == NULL)
		err_sys("malloc error");

	for ( ; ; ) {
		len = addrlen;
		if ((connfd = accept(listenfd, cliaddr, &len)) < 0)
			err_sys("connection from %s", sock_ntop(cliaddr, len));
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if (write(connfd, buff, strlen(buff)) < 0)
			err_sys("write error");
		close(connfd);
	}
}
