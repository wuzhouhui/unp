/*
 * =============================================================================
 *
 *       Filename:  sourceroute6.c
 *
 *    Description:  inet6_srcrt_print() function, for print IPv6 receive
 *		    source routing, figure 27-15, page 577.
 *
 *        Version:  1.0
 *        Created:  04/12/2015 07:21:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void inet6_srcrt_print(void *ptr)
{
	int	i, segments;
	char	str[INET6_ADDRSTRLEN];

	segments = Inet6_rth_segments(ptr);
	printf("received source route: ");
	for (i = 0; i < segments; i++) 
		printf("%s ", Inet_ntop(AF_INET6, Inet6_rth_getaddr(ptr, i),
				str, sizeof(str)));
	printf("\n");
}
