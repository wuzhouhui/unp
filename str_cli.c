/*
 * =============================================================================
 *
 *       Filename:  str_cli.c
 *
 *    Description:  str_cli function.
 *
 *        Version:  1.0
 *        Created:  03/03/2015 11:22:45 AM
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
	char	sendline[MAXLINE], recvline[MAXLINE];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {
		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated permaturely");
		Fputs(recvline, stdout);
	}
}
