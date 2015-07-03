/*
 * =============================================================================
 *
 *       Filename:  sctpserv01.c
 *
 *    Description:  SCTP streaming echo server program  
 *
 *        Version:  1.0
 *        Created:  03/12/2015 07:28:12 PM
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
	int	sock_fd, msg_flags;
	char	readbuf[BUFFSIZE];
	struct	sockaddr_in servaddr, cliaddr;
	struct	sctp_sndrcvinfo sri;
	struct	sctp_event_subscribe evnts;
	int	stream_increment = 1;
	socklen_t len;
	size_t	rd_sz;

	if (argc == 2)
		stream_increment = atoi(argv[1]);
	if ((sock_fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP)) < 0)
		err_sys("socket error");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if (bind(sock_fd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	bzero(&evnts, sizeof(evnts));
	evnts.sctp_data_io_event = 1;
	if (setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS,
				&evnts, sizeof(evnts)) < 0)
		err_sys("setsockopt error");

	if (listen(sock_fd, LISTENQ) < 0)
		err_sys("listen error");
	for ( ; ; ) {
		len = sizeof(struct sockaddr_in);
		if ((rd_sz = sctp_recvmsg(sock_fd, readbuf, sizeof(readbuf),
				(SA *)&cliaddr, &len, &sri,
				&msg_flags)) < 0)
			err_sys("recvmsg error");
		if (stream_increment) {
			sri.sinfo_stream++;
			/*	error on run. --wzh
			if (sri.sinfo_stream >=
					sctp_get_no_strms(sock_fd, (SA *)&cliaddr, len))
				sri.sinfo_stream = 0;
			*/
		}
		if (sctp_sendmsg(sock_fd, readbuf, rd_sz,
				(SA *)&cliaddr, len,
				sri.sinfo_ppid,
				sri.sinfo_flags,
				sri.sinfo_stream,
				0, 0) < 0)
			err_sys("sctp_sendmsg error");
	}
}
