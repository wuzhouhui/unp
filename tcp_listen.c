/*
 * =============================================================================
 *
 *       Filename:  tcp_listen.c
 *
 *    Description:  tcp_listen function, figure 11-12, page 329.
 *
 *        Version:  1.0
 *        Created:  03/15/2015 10:53:38 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int tcp_listen(const char *hostname, const char *service, socklen_t *addrlenp)
{
	int	listenfd, n;
	const int on = 1;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(hints));
	hints.ai_flags	= AI_PASSIVE;
	hints.ai_family	= AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((n = getaddrinfo(hostname, service, &hints, &res)) != 0)
		err_quit("tcp_listen error for %s, %s: %s",
				hostname, service, gai_strerror(n));

	ressave = res;
	do {
		if ((listenfd = socket(res->ai_family, res->ai_socktype,
				res->ai_protocol)) < 0)
			continue;
		if (setsockopt(listenfd, SOL_SOCKET,
				SO_REUSEADDR, &on, sizeof(on)) < 0) {
			close(listenfd);
			continue;
		}
		if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
			break;
		close(listenfd); /* bind error, close and try next one */
	} while ((res = res->ai_next) != NULL);

	if (res == NULL)	/* errno from final socket() or bind() */
		err_sys("tcp_listen error for %s, %s", hostname, service);
	if (listen(listenfd, LISTENQ) < 0) {
		close(listenfd);
		err_sys("tcp_listen: listen error");
	}
	
	if (addrlenp)
		*addrlenp = res->ai_addrlen;
	freeaddrinfo(ressave);
	return listenfd;
}
