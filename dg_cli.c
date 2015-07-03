/*
 * =============================================================================
 *
 *       Filename:  dg_cli.c
 *
 *    Description:  called by udpcli01.c
 *
 *        Version:  1.0
 *        Created:  03/09/2015 10:40:30 PM
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

	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if (strlen(sendline) != sendto(sockfd, sendline,
					strlen(sendline),
					0,
					pservaddr,
					servlen))
			err_sys("dg_cli: sendto error");
		if ((n = recvfrom(sockfd, recvline, MAXLINE,
						0,
						NULL,
						NULL)) < 0)
			err_sys("dg_cli: recvfrom");
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
}
