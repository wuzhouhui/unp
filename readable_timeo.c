/*
 * =============================================================================
 *
 *       Filename:  readable_timeo.c
 *
 *    Description:  readable_timeo() function: waiting for a fd become to 
 *		    readable.
 *
 *        Version:  1.0
 *        Created:  03/17/2015 10:16:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int readable_timeo(int fd, int sec)
{
	fd_set	rset;
	struct timeval tv;

	FD_ZERO(&rset);
	FD_SET(fd, &rset);

	tv.tv_sec = sec;
	tv.tv_usec = 0;

	return select(fd + 1, &rset, NULL, NULL, &tv);
}
