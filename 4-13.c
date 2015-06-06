/*
 * =============================================================================
 *
 *       Filename:  4-13.c
 *
 *    Description:  figure 4-13, page 92. NOTE: this program is just a 
 *    memo, can't run.
 *
 *        Version:  1.0
 *        Created:  03/02/2015 11:04:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

pid_t	pid;
int	listenfd, connfd;
listenfd = Socket( ... );
/*
 * fill in sockaddr_in{} with server's well-known port.
 */
Bind(listenfd, ...);
Listen(listenfd, LISTENQ);
for (;;) {
	connfd = Accept(listenfd, ... ); /* probably blocks. */
	if ((pid = Fork()) == 0) { /* child */
		Close(listenfd);	/* child closes listening socket */
		doit(connfd);	/* process the request */
		Close(connfd);	/* done with this client */
		exit(0);	/* child terminates */
	}

	/* parent */
	Close(connfd);	/* parent closes connected socket */
}
