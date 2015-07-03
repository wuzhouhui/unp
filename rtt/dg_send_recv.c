/*
 * =============================================================================
 *
 *       Filename:  dg_send_recv.c
 *
 *    Description:  dg_send_recv(). figure 22-8, page 473.
 *
 *        Version:  1.0
 *        Created:  04/05/2015 05:28:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unprtt.h"
#include <setjmp.h>

#define	RTT_DEBUG

static struct rtt_info	rttinfo;
static int	rttinit = 0;
static struct msghdr	msgsend, msgrecv;	/* assumed init to 0 */
static struct hdr {
	uint32_t	seq;	/* sequence # */
	uint32_t	ts;	/* timestamp when sent */
} sendhdr, recvhdr;

static void sig_alrm(int);
static sigjmp_buf	jmpbuf;

ssize_t dg_send_recv(int fd, const void *outbuff, size_t outbytes,
		void *inbuff, size_t inbytes,
		const SA *destaddr, socklen_t destlen)
{
	ssize_t	n;
	struct iovec	iovsend[2], iovrecv[2];

	if (rttinit == 0) {
		rtt_init(&rttinfo);	/* first time we're called */
		rttinit = 1;
		rtt_d_flags = 1;
	}

	sendhdr.seq++;
	msgsend.msg_name	= destaddr;
	msgsend.msg_namelen	= destlen;
	msgsend.msg_iov		= iovsend;
	msgsend.msg_iovlen	= 2;
	iovsend[0].iov_base	= &sendhdr;
	iovsend[0].iov_len	= sizeof(struct hdr);
	iovsend[1].iov_base	= outbuff;
	iovsend[1].iov_len	= outbytes;

	msgrecv.msg_name	= NULL;
	msgrecv.msg_namelen	= 0;
	msgrecv.msg_iov		= iovrecv;
	msgrecv.msg_iovlen	= 2;
	iovrecv[0].iov_base	= &recvhdr;
	iovrecv[0].iov_len	= sizeof(struct hdr);
	iovrecv[1].iov_base	= inbuff;
	iovrecv[1].iov_len	= inbytes;

	Signal(SIGALRM, sig_alrm);
	rtt_newpack(&rttinfo);	/* initialize for this packet */

sendagain:
	sendhdr.ts = rtt_ts(&rttinfo);
	Sendmsg(fd, &msgsend, 0);

	alarm(rtt_start(&rttinfo)); /* calc timeout value & start timer */
	if (sigsetjmp(jmpbuf, 1) != 0) {
		if (rtt_timeout(&rttinfo) < 0) {
			err_msg("dg_send_recv: no response from server, giving up");
			rtt_init = 0;	/* reinit in case we're called again */
			errno = ETIMEDOUT;
			return -1;
		}
		goto sendagain;
	}

	do {
		n = Recvmsg(fd, &msgrecv, 0);
	} while (n < sizeof(struct hdr) || recvhdr.seq != sendhdr.seq);
	alarm(0);	/* stop SIGALRM timer. */

	/* calculate & store new RTT estimator value. */
	rtt_stop(&rttinfo, rtt_ts(&rttinfo) - recvhdr.ts);

	return (n - sizeof(struct hdr)); /* return size of received datagram. */
}

static void sig_alrm(int signo)
{
	siglongjmp(jmpbuf, 1);
}
