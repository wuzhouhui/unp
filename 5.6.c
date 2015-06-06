/*
 * =============================================================================
 *
 *       Filename:  tcpcli01.c
 *
 *    Description:  TCP echo client.
 *
 *        Version:  1.0
 *        Created:  03/03/2015 11:17:42 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void sigpipe_hand(int signo)
{
	printf("catch SIGPIPE\n");
	return;
}

int main(int argc, char *argv[])
{
	int	sockfd;
	struct	sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli01 <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	= AF_INET;
	servaddr.sin_port	= htons(13);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Signal(SIGPIPE, sigpipe_hand);

	Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

	sleep(2);
	write(sockfd, "nothing", 7);
	sleep(2);
	write(sockfd, "nothing", 7);

	exit(0);
}
