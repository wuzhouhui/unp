/*
 * =============================================================================
 *
 *       Filename:  dgclibcast5.c
 *
 *    Description:  using sigsetjmp() and siglongjmp() in signal handler.
 *		    figure 20-9, page 429.
 *
 *        Version:  1.0
 *        Created:  04/02/2015 09:46:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <setjmp.h>

static void recvfrom_alarm(int);
static sigjmp_buf jmpbuf;

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	n;
	const int on = 1;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];
	socklen_t len;
	struct	sockaddr *preply_addr;

	if ((preply_addr = malloc(servlen)) == NULL)
		err_sys("dg_cli: malloc error");
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0)
		err_sys("dg_cli: setsockopt error");
	if (signal(SIGALRM, recvfrom_alarm) == SIG_ERR)
		err_sys("dg_cli: signal error");

	while (fgets(sendline, MAXLINE, fp)) {
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr,
				servlen);
		alarm(5);
		for ( ; ; ) {
			if (sigsetjmp(jmpbuf, 1) != 0)
				break;
			len = servlen;
			n = recvfrom(sockfd, recvline, MAXLINE, 0, 
					preply_addr, &len);
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
	siglongjmp(jmpbuf, 1);
}
