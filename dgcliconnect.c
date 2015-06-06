/*
 * =============================================================================
 *
 *       Filename:  dgcliconnect.c
 *
 *    Description:  function dg_cli() called connect.
 *
 *        Version:  1.0
 *        Created:  03/10/2015 09:56:28 PM
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

	if (connect(sockfd, (SA *)&pservaddr, servlen) < 0)
		err_sys("dg_cli: connect error");

	while (fgets(sendline, MAXLINE, fp) != NULL) {
		n = strlen(sendline);
		if (n != write(sockfd, sendline, n))
			err_sys("dg_cli: write error");
		if ((n = read(sockfd, recvline, MAXLINE)) < 0)
			err_sys("dg_cli: read error");
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
}
