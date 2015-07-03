/*
 * =============================================================================
 *
 *       Filename:  dgclitimeo2.c
 *
 *    Description:  dg_cli() function using SO_RCVTIMEO socket option.
 *
 *        Version:  1.0
 *        Created:  03/17/2015 10:30:44 PM
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
	int	n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];
	struct timeval tv;

	tv.tv_sec  = 5;
	tv.tv_usec = 0;
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) 
		err_sys("dg_cli: setsockopt error");
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if (sendto(sockfd, sendline, strlen(sendline), 0, pservaddr,
				servlen) < 0)
			err_sys("dg_cli: sendto error");

		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		if (n < 0) {
			if (errno == EWOULDBLOCK) {
				fprintf(stderr, "socket timeout\n");
				continue;
			} else {
				err_sys("dg_cli: recvfrom");
			}
		}
	}
}
