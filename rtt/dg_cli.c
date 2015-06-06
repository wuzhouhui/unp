/*
 * =============================================================================
 *
 *       Filename:  dg_cli.c
 *
 *    Description:  dg_cli() that call our own dg_send_recv(). figure 22-6,
 *		    page 471.
 *
 *        Version:  1.0
 *        Created:  04/05/2015 05:18:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

ssize_t Dg_send_recv(int, const void *, size_t void *, size_t,
		const SA *, socklen_t);

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	ssize_t	n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {
		n = Dg_send_recv(sockfd, sendline, strlen(sendline),
				recvline, MAXLINE, pservaddr, servlen);
		recvline[n] = 0;
		Fputs(recvline, stdout);
	}
}
