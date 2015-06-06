/*
 * =============================================================================
 *
 *       Filename:  pselect.c
 *
 *    Description:  an uncorrect but simple implementation of pselect().
 *		    figure 20-8, page 428.
 *
 *        Version:  1.0
 *        Created:  04/02/2015 09:38:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int pselect(int nfds, fd_set *rset, fd_set *wset, fd_set *xset,
		const struct timespec *ts, const sigset_t *sigmask)
{
	int	n;
	struct	timeval tv;
	sigset_t savemask;

	if (ts != NULL) {
		tv.tv_sec = ts->tv_sec;
		tv.tv_usec = ts->tv_nsec / 1000;
	}

	sigprocmask(SIG_SETMASK, sigmask, &savemask);
	n = select(nfds, rset, wset, xset, (ts == NULL) ? NULL : &tv);
	sigprocmask(SIG_SETMASK, &savemask, NULL);

	return n;
}
