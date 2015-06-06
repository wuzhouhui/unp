/*
 * =============================================================================
 *
 *       Filename:  gettimeofday.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/15/2015 02:07:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include <sys/time.h>

int Gettimeofday(struct timeval *tv, struct timezone *tz)
{
	if (gettimeofday(tv, tz) < 0)
		err_sys("gettimeofday error");
	return(0);
}
