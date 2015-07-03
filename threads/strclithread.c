/*
 * =============================================================================
 *
 *       Filename:  strclithread.c
 *
 *    Description:  str_cli() using thread. figure 26-2, page 538.
 *
 *        Version:  1.0
 *        Created:  04/09/2015 04:41:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unpthread.h"

void *copyto(void *);

static int sockfd;	/* global for both threads to access */
static FILE *fp;

void str_cli(FILE *fp_arg, int sockfd_arg)
{
	char	recvline[MAXLINE];
	pthread_t tid;

	sockfd = sockfd_arg;	/* copy arguments to externals */
	fp = fp_arg;

	Pthread_create(&tid, NULL, copyto, NULL);

	while (Readline(sockfd, recvline, MAXLINE) > 0)
		Fputs(recvline, stdout);
}

void *copyto(void *arg)
{
	char	sendline[MAXLINE];

	while (Fgets(sendline, MAXLINE, fp) != NULL)
		Writen(sockfd, sendline, strlen(sendline));
	Shutdown(sockfd, SHUT_WR); /* EOF on stdin, send FIN */

	return(NULL);
	 /* return (i.e., thread terminates) when EOF on stdin */
}
