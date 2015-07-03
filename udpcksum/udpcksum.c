/*
 * =============================================================================
 *
 *       Filename:  udpcksum.c
 *
 *    Description:  test_udp() function for send DNS request and read 
 *		    response. figure 29-10, page 635.
 *
 *        Version:  1.0
 *        Created:  04/22/2015 03:06:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "udpcksum.h"
#include <setjmp.h>

static sigjmp_buf jmpbuf;
static int canjump;

void sig_alrm(int signo) 
{
	if (canjump == 0)
		return;
	siglongjmp(jmpbuf, 1);
}

void test_udp(void)
{
	volatile int nsent = 0, timeout = 3;
	struct udpiphdr *ui;

	Signal(SIGALRM, sig_alrm);

	if (sigsetjmp(jmpbuf, 1)) {
		if (nsent >= 3)
			err_quit("no response");
		printf("timeout\n");
		timeout *= 2;	/* exponential backoff: 3, 6, 12 */
	}
	canjump = 1;	/* siglongjmp is now OK */
	send_dns_query();
	nsent++;
	
	alarm(timeout);
	ui = udp_read();
	canjump = 0;
	alarm(0);

	if (ui->ui_sum == 0)
		printf("UDP checksums off\n");
	else 
		printf("UDP checksums on\n");
	if (verbose)
		printf("received UDP checksum = %x\n", ntohs(ui->ui_sum));
}
