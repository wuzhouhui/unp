/*
 * =============================================================================
 *
 *       Filename:  daytimetcpsrv1.c
 *
 *    Description:  figure 4-11, page 89
 *
 *        Version:  1.0
 *        Created:  03/02/2015 10:37:35 PM
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

int main(int argc, char **argv)
{
	int	listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char	buff[MAXLINE];
	time_t	ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	 = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port	 = htons(9999);

	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

	/* Listen(listenfd, LISTENQ); */

	for (;;) {
		len	= sizeof(cliaddr);
		connfd	= Accept(listenfd, (SA *)&cliaddr, &len);
		printf("connection from %s, port %d\n",
				inet_ntop(AF_INET, &cliaddr.sin_addr, buff,
					sizeof(buff)),
				ntohs(cliaddr.sin_port));
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		Write(connfd, buff, strlen(buff));

		Close(connfd);
	}
}
