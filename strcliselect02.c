/*
 * =============================================================================
 *
 *       Filename:  strcliselect02.c
 *
 *    Description:  str_cli function, handle EOF correctly and using select.
 *
 *        Version:  1.0
 *        Created:  03/05/2015 04:46:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  2
 *
 * =============================================================================
 */

#include "unp.h"

void str_cli(FILE *fp, int sockfd)
{
	int	maxfdp1, stdineof;
	fd_set	rset;
	char	buf[MAXLINE];
	int	n;

	stdineof = 0;
	FD_ZERO(&rset);

	for ( ; ; ) {
		if (stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(sockfd, &rset)) { /* socket is readable */
			if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
				if (stdineof == 1)
					return;	/* normale termination */
				else 
					err_quit("str_cli: server terminated prematruely");
			}
			Write(fileno(stdout), buf, n);
		}

		if (FD_ISSET(fileno(fp), &rset)) { /* input is readable */
			if ((n = Read(fileno(fp), buf, MAXLINE)) == 0) {
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR);
				FD_CLR(fileno(fp), &rset);
				continue;
			}

			Writen(sockfd, buf, n);
		}
	}
}
