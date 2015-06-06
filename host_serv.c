/*
 * =============================================================================
 *
 *       Filename:  host_serv.c
 *
 *    Description:  function host_serv.
 *
 *        Version:  1.0
 *        Created:  03/14/2015 01:00:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

struct addrinfo *host_serv(const char *host, const char *serv,
		int family, int socktype)
{
	/* int	n; */ /* redundent --wzh */
	struct	addrinfo hints, *res;

	bzero(&hints, sizeof(hints));
	hints.ai_flags	= AI_CANONNAME;	/* always return canonical name */
	hints.ai_family	= family;	/* AF_UNSPEC, AF_INET, AF_INET6, etc. */
	hints.ai_socktype = socktype;	/* 0, SOCK_STREAM, SOCK_DGRAM, etc. */

	if (getaddrinfo(host, serv, &hints, &res) != 0)
		return NULL;
	return res;
}

struct addrinfo *Host_serv(const char *host, const char *serv,
		int family, int socktype)
{
	struct addrinfo *res = host_serv(host, serv, family, socktype);

	if (res == NULL)
		err_sys("host_serv error");
	return(res);
}
