/*
 * =============================================================================
 *
 *       Filename:  home_page.c
 *
 *    Description:  home_page() function. figure 16-16, page 357.
 *
 *        Version:  1.0
 *        Created:  03/26/2015 06:30:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "web.h"

void home_page(const char *host, const char *fname)
{
	int	fd, n;
	char	line[MAXLINE];

	if ((fd = tcp_connect(host, SERV)) < 0)
		err_sys("home_page: tcp_connect error");
	n = snprintf(line, sizeof(line), GET_CMD, fname);
	Writen(fd, line, n);

	for ( ; ; ) {
		n = read(fd, line, MAXLINE);
		if (n == 0)
			break;
		else if (n < 0)
			err_sys("home_page: read error");
	}
	printf("end-of-file on home page\n");
	close(fd);
}
