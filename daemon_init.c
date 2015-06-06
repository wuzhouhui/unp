/*
 * =============================================================================
 *
 *       Filename:  daemon_init.c
 *
 *    Description:  daemonize current prosess. figure 13-4, page 290.
 *
 *        Version:  1.0
 *        Created:  03/16/2015 02:12:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <syslog.h>

#define MAXFD 64

extern int daemon_proc;	/* defined in error.c */

int daemon_init(const char *pname, int facility)
{
	int	i;
	pid_t	pid;

	if ((pid = fork()) < 0)
		return -1;
	else if (pid)	/* parent */
		_exit(0);

	/* child continue */
	if (setsid() < 0)
		return -1;
	if (signal(SIGHUP, SIG_IGN) == SIG_ERR)
		return -1;
	if ((pid = fork()) < 0)
		return -1;
	else if (pid)
		_exit(0);

	daemon_proc = 1;
	chdir("/");
	for (i = 0; i < MAXFD; i++)
		close(i);

	/* redirect stdin, stdout, and stderr to /dev/null */
	open("/dev/null", O_RDONLY);
	open("/dev/null", O_RDWR);
	open("/dev/null", O_RDWR);

	openlog(pname, LOG_PID, facility);

	return 0;
}
