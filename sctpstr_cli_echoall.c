/*
 * =============================================================================
 *
 *       Filename:  sctpstr_cli_echoall.c
 *
 *    Description:  function sctpstr_cli_echoall, called by sctp server.
 *		    figure 10-7, page 230.
 *
 *        Version:  1.0
 *        Created:  03/13/2015 11:02:45 AM
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

#define SCTP_MAXLINE	800
#ifndef SERV_MAX_SCTP_STRM
#define SERV_MAX_SCTP_STRM 8
#endif

void sctpstr_cli_echoall(FILE *fp, int sock_fd, struct sockaddr *to,
		socklen_t tolen)
{
	struct sockaddr_in peeraddr;
	struct sctp_sndrcvinfo sri;
	char	sendline[SCTP_MAXLINE], recvline[SCTP_MAXLINE];
	socklen_t len;
	int	rd_sz, strsz, i;
	int	msg_flags;

	bzero(sendline, sizeof(sendline));
	bzero(&sri, sizeof(sri));
	while (fgets(sendline, SCTP_MAXLINE - 9, fp) != NULL) {
		strsz = strlen(sendline);
		if (sendline[strsz - 1] == '\n') {
			sendline[strsz - 1] = 0;
			strsz--;
		}
		for (i = 0; i < SERV_MAX_SCTP_STRM; i++) {
			snprintf(sendline + strsz, sizeof(sendline) - strsz,
					".msg.%d", i);
			if (sctp_sendmsg(sock_fd, sendline, sizeof(sendline),
					to, tolen, 0, 0, i, 0, 0) < 0)
				err_sys("sctp_sendmsg error");
		}
		for (i = 0; i < SERV_MAX_SCTP_STRM; i++) {
			len = sizeof(peeraddr);
			if ((rd_sz = sctp_recvmsg(sock_fd, recvline, 
					sizeof(recvline),
					(SA *)&peeraddr, &len, &sri,
					&msg_flags)) < 0)
				err_sys("sctp_recvmsg error");
			printf("From str: %d seq: %d (assoc: 0x%x",
					sri.sinfo_stream, sri.sinfo_ssn,
					(u_int)sri.sinfo_assoc_id);
			printf("%.*s\n", rd_sz, recvline);
		}
	}
}
