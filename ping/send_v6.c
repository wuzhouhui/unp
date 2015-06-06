/*
 * =============================================================================
 *
 *       Filename:  send_v6.c
 *
 *    Description:  construct and send a IPMPv6 echo request message.
 *		    figure 28-16, page 596.
 *
 *        Version:  1.0
 *        Created:  04/14/2015 10:14:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "ping.h"

void send_v6(void)
{
#ifdef	IPV6
	int	len;
	struct icmp6_hdr *icmp6;

	icmp6 = (struct icmp6_hdr *)sendbuf;
	icmp6->icmp6_type = ICMP6_ECHO_REQUEST;
	icmp6->icmp6_code = 0;
	icmp6->icmp6_id = pid;
	icmp6->icmp6_seq = nsent++;
	memset((icmp6 + 1), 0xa5, datalen); /* fill with pattern */
	Gettimeofday((struct timeval *)(icmp6 + 1), NULL);
	len = 8 + datalen;	/* 8-byte ICMPv6 header. */
	Sendto(sockfd, sendbuf, len, 0, pr->sasend, pr->salen);
	/* kernel calculates and stores checksum for us. */
#endif	/* IPV6 */
}
