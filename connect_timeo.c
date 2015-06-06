/*
 * =============================================================================
 *
 *       Filename:  connect_timeo.c
 *
 *    Description:  connect() with timeout.
 *
 *        Version:  1.0
 *        Created:  03/17/2015 09:53:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

static void connect_alarm(int);

int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nsec)
{
	Sigfunc *sigfunc;
	int	n;

	if ((sigfunc = signal(SIGALRM, connect_alarm)) == SIG_ERR)
		err_sys("connect_timeo: signal error");
	if (alarm(nsec) != 0)
		err_msg("connect_timeo: alarm was already set");
	if ((n = connect(sockfd, saptr, salen)) < 0) {
		close(sockfd);
		if (errno = EINTR)
			errno = ETIMEDOUT;
	}
	alarm(0);	/* turn off the alarm */

	/*
	 * restore previous signal handler.
	 */
	if (signal(SIGALRM, sigfunc) == SIG_ERR)
		err_sys("connect_time: signal error");

	return n;
}

static void connect_alarm(int signo)
{
	return;	/* just interrupt the connect() */
}
