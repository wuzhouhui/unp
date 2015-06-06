/*
 * =============================================================================
 *
 *       Filename:  udpcli01.c
 *
 *    Description:  echo client program using UDP.
 *
 *        Version:  1.0
 *        Created:  03/09/2015 10:36:10 PM
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
	struct	sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: udpcli <IPaddress>");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0)
		err_sys("inet_pton error");

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	dg_cli(stdin, sockfd, (SA *)&servaddr, sizeof(servaddr));

	exit(0);
}
