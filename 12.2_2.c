/*
 * =============================================================================
 *
 *       Filename:  12.2_1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/21/2015 06:28:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int main(void)
{
	int	listenfd;
	struct sockaddr_in6 servaddr;
	int	n = 1;

	if ((listenfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
		err_sys("socket failed");
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &n, sizeof(n)) < 0)
		err_sys("setsockopt for SO_REUSEADDR failed");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_addr = in6addr_any;
	servaddr.sin6_port = htons(9999);
	if (bind(listenfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind failed");
	if (listen(listenfd, LISTENQ) < 0)
		err_sys("listen failed");
	pause();
	return(0);
}
