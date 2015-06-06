/*
 * =============================================================================
 *
 *       Filename:  dgclibcast6.c
 *
 *    Description:  using pipe from signal handler to main control function 
 *		    as IPC. figure 20-10, page 430.
 *
 *        Version:  1.0
 *        Created:  04/02/2015 10:03:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

static void recvfrom_alarm(int);
static int pipefd[2];

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	n, maxfdp1;
	const int on = 1;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];
	fd_set	rset;
	socklen_t len;
	struct sockaddr *preply_addr;

	if ((preply_addr = malloc(servlen)) == NULL)
		err_sys("dg_cli: malloc error");
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0)
		err_sys("dg_cli: setsockopt error");
	if (pipe(pipefd) < 0)
		err_sys("dg_cli: pipe error");
	maxfdp1 = max(sockfd, pipefd[0]) + 1;
	FD_ZERO(&rset);
	if (signal(SIGALRM, recvfrom_alarm) == SIG_ERR)
		err_sys("dg_cli: signal error");
	while (fgets(sendline, MAXLINE, fp)) {
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr,
				servlen);
		alarm(5);
		for ( ; ; ) {
			FD_SET(sockfd, &rset);
			FD_SET(pipefd[0], &rset);
			if ((n = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
				if (errno == EINTR)
					continue;
				else 
					err_sys("select error");
			}
			if (FD_ISSET(sockfd, &rset)) {
				len = servlen;
				n = recvfrom(sockfd, recvline, MAXLINE,
						0, preply_addr, &len);
				recvline[n] = 0;
				printf("from %s: %s",
						sock_ntop_host(preply_addr,
							len), recvline);
			}

			if (FD_ISSET(pipefd[0], &rset)) {
				read(pipefd[0], &n, 1);
				break;
			}
		}
	}
	free(preply_addr);
}

static void recvfrom_alarm(int signo)
{
	write(pipefd[1], "", 1);
	return;
}
