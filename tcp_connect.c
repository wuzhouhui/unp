/*
 * =============================================================================
 *
 *       Filename:  tcp_connect.c
 *
 *    Description:  function tcp_connect: do what the client generally do.
 *
 *        Version:  1.0
 *        Created:  03/14/2015 01:12:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int tcp_connect(const char *host, const char *serv)
{
	int	sockfd, n;
	struct	addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(hints));
	hints.ai_family	= AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("tcp_connect error for %s, %s: %s",
				host, serv, gai_strerror(n));
	ressave = res;
	do {
		if ((sockfd = socket(res->ai_family, res->ai_socktype,
				res->ai_protocol)) < 0)
			continue;
		else if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0)
			close(sockfd);

		/* break once success */
	} while (res = res->ai_next);

	if (res == NULL)
		err_sys("tcp_connect error for %s, %s", host, serv);

	freeaddrinfo(ressave);
	return sockfd;
}
