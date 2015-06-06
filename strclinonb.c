/*
 * =============================================================================
 *
 *       Filename:  strclinonb.c
 *
 *    Description:  str_cli() nonblocked version.
 *
 *        Version:  1.0
 *        Created:  03/22/2015 09:22:11 PM
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
	int	maxfdp1, val, stdineof;
	ssize_t	n, nwriten;
	fd_set	rset, wset;
	char	to[MAXLINE], fr[MAXLINE];
	char	*toiptr, *tooptr, *friptr, *froptr;

	if ((val = fcntl(sockfd, F_GETFL, 0)) < 0)
		err_sys("str_cli:fcntl error with F_GETFL");
	if (fcntl(sockfd, F_SETFL, val | O_NONBLOCK) < 0)
		err_sys("str_cli:fcntl error with F_SETFL");
	if ((val = fcntl(STDIN_FILENO, F_GETFL, 0)) < 0)
		err_sys("str_cli:fcntl error for STDIN_FILENO with F_GETFL");
	if (fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK) < 0)
		err_sys("str_cli:fcntl error for STDIN_FILENO with F_SETFL");
	if ((val = fcntl(STDOUT_FILENO, F_GETFL, 0)) < 0)
		err_sys("str_cli:fcntl error for STDOUT_FILENO with F_GETFL");
	if (fcntl(STDOUT_FILENO, F_SETFL, val | O_NONBLOCK) < 0)
		err_sys("str_cli:fcntl error for STDOUT_FILENO with F_SETFL");

	toiptr = tooptr = to;
	friptr = froptr = fr;
	stdineof = 0;
	maxfdp1 = max(max(STDIN_FILENO, STDOUT_FILENO), sockfd) + 1;

	for ( ; ; ) {
		FD_ZERO(&rset);
		FD_ZERO(&wset);
		if (stdineof == 0 && toiptr < &to[MAXLINE])
			FD_SET(STDIN_FILENO, &rset);
		if (friptr < &fr[MAXLINE])
			FD_SET(sockfd, &rset);
		if (tooptr != toiptr)
			FD_SET(sockfd, &wset);
		if (froptr != friptr)
			FD_SET(STDOUT_FILENO, &wset);

		if (select(maxfdp1, &rset, &wset, NULL, NULL) < 0)
			err_sys("str_cli:select error");
		if (FD_ISSET(STDIN_FILENO, &rset)) {
			if (( n = read(STDIN_FILENO, toiptr, &to[MAXLINE]
					- toiptr)) < 0) {
				if (errno != EWOULDBLOCK)
					err_sys("read error on stdin");
			} else if (n == 0) {
				fprintf(stderr, "%s: EOF on stdin\n",
						gf_time());
				stdineof = 1;
				if (tooptr == toiptr)
					shutdown(sockfd, SHUT_WR);
			} else {
				fprintf(stderr, "%s: read %d bytes from"
						"stdin\n", gf_time(), n);
				toiptr += n;
				FD_SET(sockfd, &wset);
			}
		}

		if (FD_ISSET(sockfd, &rset)) {
			if ((n = read(sockfd, friptr, &fr[MAXLINE] - 
					friptr)) < 0) {
				if (errno != EWOULDBLOCK)
					err_sys("read error on socket");
			} else if (n == 0) {
				fprintf(stderr, "%s: EOF on socket\n",
						gf_time());
				if (stdineof)
					return;
				else 
					err_quit("str_cli: server terminated"
						"prematurely");
			} else {
				fprintf(stderr, "%s: read %d bytes from socket\n",
						gf_time(), n);
				friptr += n;
				FD_SET(STDOUT_FILENO, &wset);
			}
		}

		if (FD_ISSET(STDOUT_FILENO, &wset) &&
				((n = friptr - froptr) > 0)) {
			if ((nwriten = write(STDOUT_FILENO, froptr, n)) < 0) {
				if (errno != EWOULDBLOCK)
					err_sys("write error to stdout");
			} else {
				fprintf(stderr, "%s: wrote %d bytes to stdout\n",
						gf_time(), nwriten);
				froptr += nwriten;
				if (froptr == friptr)
					froptr = friptr = fr;
			}
		}

		if (FD_ISSET(sockfd, &wset) && 
				((n = toiptr - tooptr) > 0)) {
			if ((nwriten = write(sockfd, tooptr, n)) < 0) {
				if (errno != EWOULDBLOCK) 
					err_sys("write to socket");
			} else {
				fprintf(stderr, "%s: wrote %d bytes to socekt\n",
						gf_time(), nwriten);
				tooptr += nwriten;
				if (tooptr == toiptr) {
					toiptr = tooptr = to;
					if (stdineof)
						shutdown(sockfd, SHUT_WR);
				}
			}
		}
	}
}
