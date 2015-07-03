/*
 * =============================================================================
 *
 *       Filename:  strcliselect01.c
 *
 *    Description:  str_cli function implementation based select(), figure 6-9,
 *		    page 133.
 *
 *        Version:  1.0
 *        Created:  03/05/2015 04:18:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void str_cli(FILE *fp, int sockfd)
{
	int	maxfdp1;
	fd_set	rset;
	char	sendline[MAXLINE], recvline[MAXLINE];

	FD_ZERO(&rset);
	for ( ; ; ) {
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(sockfd, &rset)) { /* sockfd is readable */
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematruely");
			Fputs(recvline, stdout);
		}

		if (FD_ISSET(fileno(fp), &rset)) { /* input is readable */
			if (Fgets(sendline, MAXLINE, fp) == NULL)
				return;	/* all done */
			Writen(sockfd, sendline, strlen(sendline));
		}
	}
}
