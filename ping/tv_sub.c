/*
 * =============================================================================
 *
 *       Filename:  tv_sub.c
 *
 *    Description:  tv_sub() for subtracting between timeval. figure 28-7,
 *		    page 590.
 *
 *        Version:  1.0
 *        Created:  04/14/2015 08:36:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void tv_sub(struct timeval *out, struct timeval *in)
{
	if ((out->tv_usec -= in->tv_usec < 0)) {
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}
