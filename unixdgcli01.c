/*
 * =============================================================================
 *
 *       Filename:  unixdgcli01.c
 *
 *    Description:  echo client program that using UNIX domain datagram 
 *		    protocol.
 *
 *        Version:  1.0
 *        Created:  03/21/2015 03:12:38 PM
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
	struct	sockaddr_un cliaddr, servaddr;

	if ((sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sun_family = AF_LOCAL;
	strcpy(cliaddr.sun_path, tmpnam(NULL));

	if (bind(sockfd, (SA *)&cliaddr, sizeof(cliaddr)) < 0)
		err_sys("bind error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXDG_PATH);

	dg_cli(stdin, sockfd, (SA *)&servaddr, sizeof(servaddr));
	exit(0);
}
