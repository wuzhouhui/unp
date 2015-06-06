/*
 * =============================================================================
 *
 *       Filename:  tcpcli04.c
 *
 *    Description:  client based tcp that connected server 5 times.
 *
 *        Version:  1.0
 *        Created:  2015年03月04日 07时10分32秒
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
	int	i, sockfd[5];
	struct	sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: tcplic04 <IPaddress>");

	for (i = 0; i < 5; i++) {
		sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family	= AF_INET;
		servaddr.sin_port	=  htons(SERV_PORT);
		Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

		Connect(sockfd[i], (SA *)&servaddr, sizeof(servaddr));
	}

	str_cli(stdin, sockfd[0]);
	exit(0);
}
