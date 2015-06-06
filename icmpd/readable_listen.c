/*
 * =============================================================================
 *
 *       Filename:  readable_listen.c
 *
 *    Description:  handling new client connection. figure 28-36,
 *		    page 616.
 *
 *        Version:  1.0
 *        Created:  04/17/2015 01:07:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "icmpd.h"

int readable_listen(void)
{
	int	i, connfd;
	socklen_t clilen;

	clilen = sizeof(cliaddr);
	connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);

	/* find first available client[] structure */
	for (i = 0; i < FD_SETSIZE; i++)
		if (client[i].connfd < 0) {
			client[i].connfd = connfd; /* save descriptor */
			break;
		}
	if (i == FD_SETSIZE) {
		close(connfd);	  /* can't handle new client */
		return(--nready); /* rudely close the new connection */
	}
	printf("new connection, i = %d, connfd = %d\n", i, connfd);

	FD_SET(connfd, &allset); /* add new descriptor to set */
	if (connfd > maxfd)
		maxfd = connfd;	/* for select() */
	if (i > maxi)
		maxi = i;	/* max index in client[] array */
	return(--nready);
}
