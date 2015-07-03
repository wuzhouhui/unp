/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  main() of SAP/SDP declaration receive program.
 *		    figure 21-14, page 451.
 *
 *        Version:  1.0
 *        Created:  04/04/2015 10:49:19 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

#define SAP_NAME "sap.mcast.net" /* default group name and port */
#define SAP_PORT "9875"

int main(int argc, char *argv[])
{
	int	sockfd;
	const int on = 1;
	socklen_t salen;
	struct sockaddr *sa;

	if (argc == 1)
		sockfd = Udp_client(SAP_NAME, SAP_PORT, (SA **)&sa, &salen);
	else if (argc == 4)
		sockfd = Udp_aclient(argv[1], argv[2], (SA **)&sa, &salen);
	else 
		err_quit("usage: mysdr <mcast-addr> <port#> <interface-name>");
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		err_sys("setsockopt error");
	if (bind(sockfd, sa, salen) < 0)
		err_sys("bind error");
	Mcast_join(sockfd, sa, salen, (argc == 4 ? argv[3] : NULL), 0);
	loop(sockfd, salen);
	exit(0);
}
