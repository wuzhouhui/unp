/*
 * =============================================================================
 *
 *       Filename:  sendto.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/15/2015 02:09:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include <sys/types.h>
#include <sys/socket.h>

ssize_t Sendto(int sockfd, const void *buf, size_t len, int flags,
		const struct sockaddr *dest_addr, socklen_t addrlen)
{
	ssize_t	res = sendto(sockfd, buf, len, flags, dest_addr, addrlen);
	if (res < 0)
		err_sys("sendto error");
	return(res);
}
