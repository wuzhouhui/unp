/*
 * =============================================================================
 *
 *       Filename:  send_v4.c
 *
 *    Description:  construct and send a IPCMv4 echo request.
 *		    figure 28-14, page 594.
 *
 *        Version:  1.0
 *        Created:  04/14/2015 09:45:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "ping.h"

void send_v4(void)
{
	int	len;
	struct icmp *icmp;

	icmp = (struct icmp *)sendbuf;
	icmp->icmp_type	= ICMP_ECHO;
	icmp->icmp_code	= 0;
	icmp->icmp_id	= pid;
	icmp->icmp_seq	= nsent++;
	memset(icmp->icmp_data, 0xa5, datalen); /* fill with pattern */
	Gettimeofday((struct timeval *)icmp->icmp_data, NULL);

	len = 8 + datalen;
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = in_cksum((u_short *)icmp, len);

	Sendto(sockfd, sendbuf, len, 0, pr->sasend, pr->salen);
}
