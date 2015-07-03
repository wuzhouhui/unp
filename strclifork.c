/*
 * =============================================================================
 *
 *       Filename:  strclifork.c
 *
 *    Description:  str_cli() uses fork(). figure 16-10, page 350.
 *
 *        Version:  1.0
 *        Created:  03/24/2015 10:38:43 PM
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
	pid_t	pid;
	char	sendline[MAXLINE], recvline[MAXLINE];

	if ((pid = fork()) < 0) {
		err_sys("str_cli: fork error");
	} else if (pid == 0) {
		while (readline(sockfd, recvline, MAXLINE) > 0)
			fputs(recvline, stdout);

		kill(getppid(), SIGTERM); /* in case parent still running */
		exit(0);
	}

	/* parent: stdin -> server */
	while (fgets(sendline, MAXLINE, fp) != NULL)
		writen(sockfd, sendline, strlen(sendline));
	shutdown(sockfd, SHUT_WR);
	pause();
	return;
}
