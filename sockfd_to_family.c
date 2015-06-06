/*
 * =============================================================================
 *
 *       Filename:  sockfd_to_family.c
 *
 *    Description:  address family that return socket.
 *
 *        Version:  1.0
 *        Created:  03/03/2015 09:58:16 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int sockfd_to_family(int sockfd)
{
	struct sockaddr_storage ss;
	socklen_t len;

	len = sizeof(ss);
	if (getsockname(sockfd, (SA *)&ss, &len) < 0)
		return -1;
	return ss.ss_family;
}
