/*
 * =============================================================================
 *
 *       Filename:  str_echo.c
 *
 *    Description:  str_echo function.
 *
 *        Version:  1.0
 *        Created:  03/03/2015 11:03:54 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void str_echo(int sockfd)
{
	ssize_t	n;
	char	buf[MAXLINE];

again:
	while ((n = read(sockfd, buf, sizeof(buf))) > 0)
		if (write(sockfd, buf, n) < 0)
			err_sys("write error");
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("str_echo: read error");
}
