/*
 * =============================================================================
 *
 *       Filename:  dgclitimeo3.c
 *
 *    Description:  dg_cli() that using alarm to timeout recvfrom().
 *
 *        Version:  1.0
 *        Created:  03/17/2015 10:06:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

static void sig_alrm(int);

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("dg_cli: signal error");

	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if (sendto(sockfd, sendline, strlen(sendline), 0,
				pservaddr, servlen) < 0)
			err_sys("dg_cli: sendto error");
		alarm(5);
		if ((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL,
				NULL)) < 0) {
			if (errno = EINTR)
				fprintf(stderr, "socket timeout\n");
			else 
				err_sys("recvfrom error");
		} else {
			alarm(0);
			recvline[n] = 0;
			fputs(recvline, stdout);
		}
	}
}

static void sig_alrm(int signo)
{
	return;	/* just interrupt the recvfrom() */
}
