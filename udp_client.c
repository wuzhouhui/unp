/*
 * =============================================================================
 *
 *       Filename:  udp_client.c
 *
 *    Description:  udp_client function, for creating a unconnected UDP socket.
 *		    figure 11-15, page 262.
 *
 *        Version:  1.0
 *        Created:  03/15/2015 12:25:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenp)
{
	int	sockfd, n;
	struct	addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("udp_client error for %s, %s: %s",
				host, serv, gai_strerror(n));

	ressave = res;
	do {
		sockfd = socket(res->ai_family, res->ai_socktype,
				res->ai_protocol);
		if (sockfd >= 0)
			break;
	} while ((res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("udp_client error for %s, %s", host, serv);

	if ((*saptr = malloc(res->ai_addrlen)) == NULL)
		err_sys("udp_client: malloc error");
	memcpy(*saptr, res->ai_addr, res->ai_addrlen);
	*lenp = res->ai_addrlen;
	freeaddrinfo(ressave);

	return sockfd;
}
