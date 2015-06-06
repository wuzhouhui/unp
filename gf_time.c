/*
 * =============================================================================
 *
 *       Filename:  gf_time.c
 *
 *    Description:  gf_time() returns string stands time.
 *
 *        Version:  1.0
 *        Created:  03/24/2015 10:29:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <time.h>

char *gf_time(void)
{
	struct timeval	tv;
	static char	str[30];
	char	*ptr;

	if (gettimeofday(&tv, NULL) < 0)
		err_sys("gettimeofday error");

	ptr = ctime(&tv.tv_sec);
	strcpy(str, &ptr[11]);
	snprintf(str + 8, sizeof(str) - 8, ".%06ld", tv.tv_sec);
	return str;
}
