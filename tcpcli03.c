/*
 * =============================================================================
 *
 *       Filename:  tcpcli03.c
 *
 *    Description:  send RST TCP packet to echo server program after
 *		    build connection. figure 16-21, page 362
 *
 *        Version:  1.0
 *        Created:  03/26/2015 07:25:19 PM
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
	struct linger ling;
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	 = AF_INET;
	servaddr.sin_port	 = htons(SERV_PORT);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0)
		err_sys("inet_pton error");
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	ling.l_onoff	= 1;
	ling.l_linger	= 0;
	if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling)) < 0)
		err_sys("setsockopt error");
	close(sockfd);
	exit(0);
}
