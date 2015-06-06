/*
 * =============================================================================
 *
 *       Filename:  recv_v6.c
 *
 *    Description:  recv_v6(), reading and process ICMPv6 message.
 *		    figure 28-24, page 605.
 *
 *        Version:  1.0
 *        Created:  04/16/2015 02:23:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "trace.h"

extern int gotalarm;

/*
 * return:
 *	-3	timeout;
 *	-2	ICMP time exceeded in transit (caller keeps goint)
 *	-1	ICMP port unreachable (caller is done)
 *	>= 0	return value is some other ICMP unreachable code
 */
int recv_v6(int seq, struct timeval *tv)
{
#ifdef	IPV6
	int	hlen2, icmp6len, ret;
	ssize_t	n;
	socklen_t len;
	struct ip6_hdr *hip6;
	struct icmp6_hdr *icmp6;
	struct udphdr *udp;

	gotalarm = 0;
	alarm(3);
	for ( ; ; ) {
		if (gotalarm)
			return(-3); /* alarm expired */
		len = pr->salen;
		n = recvfrom(recvfd, recvbuf, sizeof(recvbuf), 0, 
				pr->sarecv, &len);
		if (n < 0) {
			if (errno == EINTR)
				continue;
			else
				err_sys("recvfrom error");
		}

		icmp6 = (struct icmp6_hdr *)recvbuf; /* ICMP header */
		if ((icmp6len = n) < 8)
			continue; /* not enough to look at ICMP header */
		if (icmp6->icmp6_type == ICMP6_TIME_EXCEEDED &&
			icmp6->icmp6_code == ICMP6_TIME_EXCEED_TRANSIT) {
			if (icmp6len < 8 + sizeof(struct ip6_hdr) + 4) 
				continue; /* not enough data to look at inner header */
			hip6 = (struct ip6_hdr *)(recvbuf + 8);
			hlen2 = sizeof(struct ip6_hdr);
			udp = (struct udphdr *)(recvbuf + 8 + hlen2);
			if (hip6->ip6_nxt == IPPROTO_UDP &&
				udp->uh_sport == htons(sport) &&
				udp->uh_dport == htons(dport + seq))
				ret = -2;

			break;
		} else if (icmp6->icmp6_type == ICMP6_DST_UNREACH) {
			if (icmp6len < 8 + sizeof(struct ip6_hdr) + 4)
				continue; /* not enough data to look at inner header */

			hip6 = (struct ip6_hdr *)(recvbuf + 8);
			hlen2 = sizeof(struct ip6_hdr);
			udp = (struct udphdr *)(recvbuf + 8 + hlen2);
			if (hip6->ip6_nxt == IPPROTO_UDP &&
				udp->uh_sport == htons(sport) &&
				udp->uh_dport == htons(dport + seq)) {
				if (icmp6->icmp6_code == ICMP6_DST_UNREACH_NOPORT)
					ret = -1;
				else 
					ret = icmp6->icmp6_code;
				break;
			}
		} else if (verbose) {
			printf(" (from %s: type = %d, code = %d)\n",
				Sock_ntop_host(pr->sarecv, pr->salen),
				icmp6->icmp6_type, icmp6->icmp6_code);
		}
		/* some other ICMP error, recvfrom() again */
	}
	alarm(0);	/* don't leave alarm running */
	Gettimeofday(tv, NULL);	/* get time of packet arrival */
	return(ret);
#endif
}
