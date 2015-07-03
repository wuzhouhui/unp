/*
 * =============================================================================
 *
 *       Filename:  icmpd.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2015 04:12:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */
#include "unpicmpd.h"

struct client {
	int	connfd;	/* Unix domain stream socket to client */
	int	family;	/* AF_INET or AF_INET6 */
	int	lport;	/* local port bound to client's UDP socket */
	/* network byte ordered */
} client[FD_SETSIZE];

/* globals */
int	fd4, fd6, listenfd, maxi, maxfd, nready;
fd_set	rset, allset;
struct sockaddr_un cliaddr;

/* function prototype */
int	readable_conn(int);
int	readable_listen(void);
int	readable_v4(void);
int	readable_v6(void);
