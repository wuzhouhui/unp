/*
 * =============================================================================
 *
 *       Filename:  daytimetcpcli.c
 *
 *    Description:  exercise 7.2, change figure 1-5 according to the 
 *		    requiments.
 *
 *        Version:  1.0
 *        Created:  03/01/2015 08:56:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <netinet/tcp.h>

int main(int argc, char **argv)
{
	int	sockfd, rcvbuf, mss;
	socklen_t len;
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: rcvbuf <IPaddrress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	len = sizeof(rcvbuf);
	Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);
	len = sizeof(mss);
	Getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &mss, &len);
	printf("defaults: SO_RCVBUF = %d, MSS = %d\n", rcvbuf, mss);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	= AF_INET;
	servaddr.sin_port	= htons(13);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

	len = sizeof(rcvbuf);
	Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);
	len = sizeof(mss);
	Getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &mss, &len);
	printf("alter connect: SO_RCVBUF = %d, MSS = %d\n", rcvbuf, mss);

	exit(0);
}
