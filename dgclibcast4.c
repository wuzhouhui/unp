/*
 * =============================================================================
 *
 *       Filename:  dgclibcast4.c
 *
 *    Description:  block and unblock signal by pselect(), figure 20-7,
 *		    page 427.
 *
 *        Version:  1.0
 *        Created:  04/02/2015 09:20:35 PM
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

void dg_cli(FILE *fp, int sockfd, const SA *pseraddr, socklen_t servlen)
{
	int	n;
	const int on = 1;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];
	fd_set	rset;
	sigset_t sigset_alrm, sigset_empty;
	socklen_t len;
	struct sockaddr *preply_addr;

	if ((preply_addr = malloc(servlen)) == NULL)
		err_sys("dg_cli: malloc error");
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0)
		err_sys("dg_cli: setsockopt error");
	FD_ZERO(&rset);
	sigemptyset(&sigset_empty);
	sigemptyset(&sigset_alrm);
	sigaddset(&sigset_alrm, SIGALRM);
	if (signal(SIGALRM, recvfrom_alarm) == SIG_ERR)
		err_sys("dg_cli: signal error");

	while (fgets(sendline, MAXLINE, fp)) {
		sendto(sockfd, sendline, strlen(sendline), 0, pseraddr, servlen);
		if (sigprocmask(SIG_BLOCK, &sigset_alrm, NULL) < 0)
			err_sys("dg_cli: sigprocmask error");
		alarm(5);
		for ( ; ; ) {
			FD_SET(sockfd, &rset);
			n = pselect(sockfd + 1, &rset, NULL, NULL, NULL, &sigset_empty);
			if (n < 0) {
				if (errno == EINTR)
					break;
				else 
					err_sys("dg_cli: pselect error");
			} else if (n != 1) {
				err_sys("dg_cli: pselect error: returned %d", n);
			}
			
			len = servlen;
			n = recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
			recvline[n] = 0;
			printf("from %s: %s",
					sock_ntop_host(preply_addr, len),
					recvline);
		}
	}
	free(preply_addr);
}

static void recvfrom_alarm(int signo)
{
	return;
}
