/*
 * =============================================================================
 *
 *       Filename:  cleanup.c
 *
 *    Description:  cleanup() function. figure 29-18, page 641.
 *
 *        Version:  1.0
 *        Created:  04/23/2015 01:13:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "udpcksum.h"

void cleanup(int signo)
{
	struct pcap_stat stat;

	putc('\n', stdout);
	if (verbose) {
		if (pcap_stats(pd, &stat) < 0)
			err_quit("pcap_stats: %s\n", pcap_geterr(pd));
		printf("%d packets received by filter\n", stat.ps_recv);
		printf("%d packets dropped by kernel\n", stat.ps_drop);
	}
	exit(0);
}
