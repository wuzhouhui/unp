/*
 * =============================================================================
 *
 *       Filename:  unixstrcli01.c
 *
 *    Description:  echo client program using unix domain byte stream 
 *		    protocol.
 *
 *        Version:  1.0
 *        Created:  03/20/2015 11:11:11 PM
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
	struct	sockaddr_un servaddr;

	if ((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");
	str_cli(stdin, sockfd);
	exit(0);
}
