/*
 * =============================================================================
 *
 *       Filename:  udp_connect.c
 *
 *    Description:  udp_connect() for creating a connected UDP socket.
 *		    figure 11-17, page 264.
 *
 *        Version:  1.0
 *        Created:  03/15/2015 12:54:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int udp_connect(const char *host, const char *serv)
{
	int	sockfd, n;
	struct	addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("udp_connect error for %s, %s: %s",
				host, serv, gai_strerror(n));

	ressave = res;
	do {
		sockfd = socket(res->ai_family, res->ai_socktype,
				res->ai_protocol);
		if (sockfd < 0)
			continue;
		if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;
		close(sockfd);
	} while ((res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("udp_connect error for %s, %s", host, serv);
	freeaddrinfo(ressave);
	return sockfd;
}
