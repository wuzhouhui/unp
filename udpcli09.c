/*
 * =============================================================================
 *
 *       Filename:  udpcli09.c
 *
 *    Description:  UDP program for determiming that out interface using 
 *		    connect. figure 8-23, page 204.
 *
 *        Version:  1.0
 *        Created:  03/10/2015 10:29:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int main(int argc, char **argv)
{
	int	sockfd;
	socklen_t len;
	struct sockaddr_in cliaddr, servaddr;

	if (argc != 2)
		err_quit("usage: udpcli <IPaddress>");

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0)
		err_sys("inet_pton error");
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	len = sizeof(cliaddr);
	if (getsockname(sockfd, (SA *)&cliaddr, &len) < 0)
		err_sys("getsockname error");
	printf("local address %s\n", sock_ntop((SA *)&cliaddr, len));

	exit(0);
}
