/*
 * =============================================================================
 *
 *       Filename:  sctpstr_cli.c
 *
 *    Description:  sctpstr_cli function called by sctp client. figure 10-4,
 *		    page 227.
 *
 *        Version:  1.0
 *        Created:  03/12/2015 10:11:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <netinet/sctp.h>	/* --wzh */

void sctpstr_cli(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen)
{
	struct	sockaddr_in peeraddr;
	struct	sctp_sndrcvinfo sri;
	char	sendline[MAXLINE], recvline[MAXLINE];
	socklen_t len;
	int	out_sz, rd_sz;
	int	msg_flags;

	bzero(&sri, sizeof(sri));
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if (sendline[0] != '[') {
			printf("Error, line must be of the form '[streamnum]text'\n");
			continue;
		}
		sri.sinfo_stream = strtol(&sendline[1], NULL, 0);
		out_sz = strlen(sendline);
		if (sctp_sendmsg(sock_fd, sendline, out_sz,
					to, tolen, 0, 0, sri.sinfo_stream,
					0, 0) < 0)
			err_sys("sctp_sendmsg error");
		len = sizeof(peeraddr);
		if ((rd_sz = sctp_recvmsg(sock_fd, recvline, sizeof(recvline),
						(SA *)&peeraddr, &len,
						&sri, &msg_flags)) < 0)
			err_sys("sctp_recvmsg error");
		printf("From str: %d seq: %d (assoc: 0x%x:",
				sri.sinfo_stream, sri.sinfo_ssn,
				(u_int)sri.sinfo_assoc_id);
		printf("%.*s", rd_sz, recvline);
	}
}
