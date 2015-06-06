/*
 * =============================================================================
 *
 *       Filename:  heartbeatcli.c
 *
 *    Description:  heart beat function for client. figure 24-14, page 522.
 *
 *        Version:  1.0
 *        Created:  04/09/2015 12:18:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

static int	servfd;
static int	nsec;		/* #seconds between each alarm. */
static int	maxnprobes;	/* #probes w/no response before quit */
static int	nprobes;	/* #probes since last server response */
static void	sig_urg(int), sig_alrm(int);

void heartbeat_cli(int servfd_arg, int nsec_arg, int maxnprobes_arg)
{
	servfd	= servfd_arg;	/* set globals for signal handlers */
	if ((nsec = nsec_arg) < 1)
		nsec = 1;
	if ((maxnprobes = maxnprobes_arg) < nsec)
		maxnprobes = nsec;
	nprobes = 0;

	Signal(SIGURG, sig_urg);
	Fcntl(servfd, F_SETOWN, getpid());

	Signal(SIGALRM, sig_alrm);
	alarm(nsec);
}

static void sig_urg(int signo)
{
	char	c;

	if (recv(servfd, &c, 1, MSG_OOB) < 0) {
		if (errno != EWOULDBLOCK)
			err_sys("recv error");
	}
	nprobes = 0;	/* reset counter */
	return;		/* may interrupt client code */
}

static void sig_alrm(int signo)
{
	if (++nprobes > maxnprobes) {
		fprintf(stderr, "server is unreachable\n");
		exit(0);
	}
	Send(servfd, "1", 1, MSG_OOB);
	alarm(nsec);
	return;	/* may interrupt client code */
}
