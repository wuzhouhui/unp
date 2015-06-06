/*
 * =============================================================================
 *
 *       Filename:  dgclitimeo1.c
 *
 *    Description:  dg_cli() function using readable_timeo() to set timeout.
 *
 *        Version:  1.0
 *        Created:  03/17/2015 10:20:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	n, ret;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if (sendto(sockfd, sendline, strlen(sendline), 0, 
				pservaddr, servlen) < 0)
			err_sys("dg_cli: sendto error");
		if ((ret = readable_timeo(sockfd, 5)) == 0) {
			fprintf(stderr, "socket timeout\n");
		} else if (ret > 0) {
			if ((n = recvfrom(sockfd, recvline, MAXLINE, 0,
					NULL, NULL)) < 0)
				err_sys("dg_cli: recvfrom error");
			recvline[n] = 0;
			fputs(recvline, stdout);
		} else {
			err_sys("dg_cli: readable_timeo error");
		}
	}
}
