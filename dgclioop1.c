/*
 * =============================================================================
 *
 *       Filename:  dgclioop1.c
 *
 *    Description:  function dg_cli that write a fixed number of 
 *		    datagram to server, figure 8-19, page 200.
 *
 *        Version:  1.0
 *        Created:  03/10/2015 10:01:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

#define NDG	2000	/* datagrams to send */
#define DGLEN	1400	/* length of each datagram */

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	i;
	char	sendline[DGLEN];

	for (i = 0; i < NDG; i++) {
		if (DGLEN != sendto(sockfd, sendline,
					DGLEN,
					0,
					pservaddr,
					servlen))
			err_ret("dg_cli: sendto error");
	}
}
