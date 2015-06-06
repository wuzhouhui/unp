/*
 * =============================================================================
 *
 *       Filename:  sctpclient01.c
 *
 *    Description:  SCTP streaming echo client program, figure 10-3,
 *		    page 291.
 *
 *        Version:  1.0
 *        Created:  03/12/2015 09:49:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <netinet/sctp.h> /* --wzh */

int main(int argc, char *argv[])
{
	int	sock_fd;
	struct	sockaddr_in servaddr;
	struct	sctp_event_subscribe evnts;
	int	echo_to_all = 0;

	if (argc < 2)
		err_quit("Missing host argument - use '%s host [echo'\n", argv[0]);
	if (argc > 2) {
		printf("Echoing message to all streams\n");
		echo_to_all = 1;
	}
	if ((sock_fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP)) < 0)
		err_sys("socket error");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	= AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port	= htons(SERV_PORT);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0)
		err_sys("inet_pton error");

	bzero(&evnts, sizeof(evnts));
	evnts.sctp_data_io_event = 1;
	if (setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &evnts, sizeof(evnts)) < 0)
		err_sys("setsockopt error");
	if (echo_to_all == 0)
		sctpstr_cli(stdin, sock_fd, (SA *)&servaddr, sizeof(servaddr));
	else 
		sctpstr_cli_echoall(stdin, sock_fd, (SA *)&servaddr,
				sizeof(servaddr));
	close(sock_fd);
	return 0;
}
