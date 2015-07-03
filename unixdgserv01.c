/*
 * =============================================================================
 *
 *       Filename:  unixdgserv01.c
 *
 *    Description:  echo server program using unix datagram protocol
 *
 *        Version:  1.0
 *        Created:  03/20/2015 11:18:49 PM
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
	struct	sockaddr_un servaddr, cliaddr;

	if ((sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");
	unlink(UNIXDG_PATH);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXDG_PATH);

	if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");
	dg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
}
