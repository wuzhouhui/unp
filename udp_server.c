/*
 * =============================================================================
 *
 *       Filename:  udp_server.c
 *
 *    Description:  udp_server() creates a unconnected socket for UDP server.
 *		    figure 11-18, page 265.
 *
 *        Version:  1.0
 *        Created:  03/15/2015 01:03:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int udp_server(const char *host, const char *serv, socklen_t *addrlen)
{
	int	sockfd, n;
	struct	addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(hints));
	hints.ai_flags	= AI_PASSIVE;
	hints.ai_family	= AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("udp_server error for %s, %s: %s",
				host, serv, gai_strerror(n));

	ressave = res;
	do {
		sockfd = socket(res->ai_family, res->ai_socktype,
				res->ai_protocol);
		if (sockfd < 0)
			continue;
		if (bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;
		close(sockfd);
	} while ((res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("udp_server error for %s, %s", host, serv);
	if (addrlen)
		*addrlen = res->ai_addrlen;

	freeaddrinfo(ressave);
	return sockfd;
}
