/*
 * =============================================================================
 *
 *       Filename:  daytimetcpsrv3.c
 *
 *    Description:  protocol independent time get server program, started 
 *		    by inetd. figure 13-12, page 298.
 *
 *        Version:  1.0
 *        Created:  03/16/2015 09:23:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <time.h>

int main(int argc, char *argv[])
{
	socklen_t len;
	struct	sockaddr *cliaddr;
	char	buff[MAXLINE];
	time_t	ticks;

	daemon_inetd(argv[0], 0);

	if ((cliaddr = malloc(sizeof(struct sockaddr_storage))) == NULL)
		err_sys("malloc error");
	len = sizeof(struct sockaddr_storage);
	if (getpeername(0, cliaddr, &len) < 0)
		err_sys("getpeername error");
	err_msg("connection from %s", sock_ntop(cliaddr, len));

	ticks = time(NULL);
	snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
	if (write(0, buff, strlen(buff)) < 0)
		err_sys("write error");
	close(0);	/* close TCP connection */
	exit(0);
}
