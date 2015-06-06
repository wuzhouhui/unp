/*
 * =============================================================================
 *
 *       Filename:  dgclibcast1.c
 *
 *    Description:  dg_cli() using broadcast. figure 20-5, page 423.
 *
 *        Version:  1.0
 *        Created:  04/02/2015 08:25:59 PM
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

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	n;
	const int on = 1;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];
	socklen_t len;
	struct sockaddr *preply_addr;

	if ((preply_addr = malloc(servlen)) == NULL)
		err_sys("dg_cli: malloc error");
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0) 
		err_sys("dg_cli: setsockopt error");
	if (signal(SIGALRM, recvfrom_alarm) == SIG_ERR)
		err_sys("dg_cli: signal error");
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if (sendto(sockfd, sendline, strlen(sendline), 0,
					pservaddr, servlen)
				!= strlen(sendline))
			err_sys("dg_cli: sendto error");
		alarm(5);
		for ( ; ; ) {
			len = servlen;
			n = recvfrom(sockfd, recvline, MAXLINE, 0, 
					preply_addr, &len);
			if (n < 0) {
				if (errno = EINTR)
					break;
				else 
					err_sys("dg_cli: recvfrom error");
			} else {
				recvline[n] = 0;
				printf("from %s: %s",
						sock_ntop_host(preply_addr,
							len),
						recvline);
			}
		}
	}
	free(preply_addr);
}

static void recvfrom_alarm(int signo)
{
	return; /* just interrupt the recvfrom() */
}
