/*
 * =============================================================================
 *
 *       Filename:  rtt.c
 *
 *    Description:  macro RTT_RTOCALC and function rtt_minmax() and 
 *		    rtt_init(), figure 22-11, page 476.
 *
 *        Version:  1.0
 *        Created:  04/05/2015 06:42:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unprtt.h"
int	rtt_d_flag = 0;	/* debug flag; can be set by caller. */

/*
 * calculate the RTO(ReTransmit Timeout) value based on current estimators:
 *	smoothed RTT(Round Trip Time) plus four times the deviation.
 */
#define RTT_RTOCALC(ptr) ((ptr)->rtt_srtt + (4.0 * (ptr)->rtt_rttvar))

static float rtt_minmax(float rto)
{
	if (rto < RTT_RXTMIN)
		rto = RTT_RXTMIN;
	else if (rto > RTT_RXTMAX)
		rto = RTT_RXTMAX;
	return rto;
}

void rtt_init(struct rtt_info *ptr)
{
	struct timeval	tv;

	Gettimeofday(&tv, NULL);
	ptr->rtt_base = tv.tv_sec; /* # sec since 1/1/1970 at start */

	ptr->rtt_rtt	= 0;
	ptr->rtt_srtt	= 0;
	ptr->rtt_rttvar	= 0.75;
	ptr->rtt_rto	= rtt_minmax(RTT_RTOCALC(ptr));
	/* first RTO at (srtt + (4 * rttvar)) = 3 seconds */
}

uint32_t rtt_ts(struct rtt_info *ptr)
{
	uint32_t ts;
	struct timeval tv;

	Gettimeofday(&tv, NULL);
	ts = ((tv.tv_sec - ptr->rtt_base) * 1000) + (tv.tv_usec / 1000);
	return ts;
}

void rtt_newpack(struct rtt_info *ptr)
{
	ptr->rtt_nrexmt = 0;
}

int rtt_start(struct rtt_info *ptr)
{
	return (int)(ptr->rtt_rto + 0.5); /* round float to int */
	/* return value can be used as: alarm(rtt_start(&foo)) */
}

void rtt_stop(struct rtt_info *ptr, uint32_t ms)
{
	double delta;

	ptr->rtt_rtt = ms / 1000.0; /* mesured RTT in seconds */

	/*
	 * unpack our estimators of RTT and mean deviation of RTT.
	 * See Jacobson's SIGCOMM '88 paper, Appendix A, for the details.
	 * We use floating point here for simplicity.
	 */

	delta = ptr->rtt_rtt - ptr->rtt_srtt;
	ptr->rtt_srtt += delta / 8; /* g = 1/8 */

	if (delta < 0.0)
		delta = -delta;	/* |delta| */

	ptr->rtt_rttvar += (delta - ptr->rtt_rttvar) / 4;
	ptr->rtt_rto = rtt_minmax(RTT_RTOCALC(ptr));
}

int rtt_timeout(struct rtt_info *ptr)
{
	ptr->rtt_rto *= 2;	/* next RTO */
	if (++ptr->rtt_nrexmt > RTT_MAXNREXMT)
		return -1; /* time to give up for this packet */
	return 0;
}
