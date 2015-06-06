/*
 * =============================================================================
 *
 *       Filename:  udpserv01.c
 *
 *    Description:  echo server program using UDP.
 *
 *        Version:  1.0
 *        Created:  03/09/2015 10:25:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int main(int argc, char *argv[])
{
	int	sockfd;
	struct	sockaddr_in servaddr, cliaddr;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	= AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port	= htons(SERV_PORT);

	if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	dg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
}
