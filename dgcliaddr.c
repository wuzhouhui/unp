/*
 * =============================================================================
 *
 *       Filename:  dgcliaddr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/09/2015 10:50:28 PM
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
	socklen_t len;
	struct sockaddr *preply_addr;

	if ((preply_addr = malloc(servlen)) == NULL)
		err_sys("dg_cli: malloc error");
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if (strlen(sendline) != sendto(sockfd,
					sendline,
					strlen(sendline),
					0,
					pservaddr,
					servlen))
			err_sys("dg_cli: sendto error");

		len = servlen;
		if ((n = recvfrom(sockfd, recvline, MAXLINE,
						0,
						preply_addr,
						&len)) < 0)
			err_sys("dg_cli: recvfrom error");
		if (len != servlen || memcmp(pservaddr, preply_addr,
					len) != 0)
			printf("replay from %s (ignored)\n",
					sock_ntop(preply_addr, len));
		continue;
	}

	recvline[n] = 0;
	fputs(recvline, stdout);
}
