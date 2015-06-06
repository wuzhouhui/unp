/*
 * =============================================================================
 *
 *       Filename:  unixbind.c
 *
 *    Description:  bind() a path for a unix domain socket. figure 15-2,
 *		    page 325.
 *
 *        Version:  1.0
 *        Created:  03/19/2015 10:22:20 PM
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
	socklen_t len;
	struct sockaddr_un addr1, addr2;

	if (argc != 2)
		err_quit("usage: unixbind <pathname>");

	if ((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");
	unlink(argv[1]);	/* ok if this fails */
	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = AF_LOCAL;
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) - 1);
	if (bind(sockfd, (SA *)&addr1, SUN_LEN(&addr1)) < 0)
		err_sys("bind error");
	len = sizeof(addr2);
	if (getsockname(sockfd, (SA *)&addr2, &len) < 0 )
		err_sys("getsockname error");
	printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
	exit(0);
}
