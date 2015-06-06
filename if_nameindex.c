/*
 * =============================================================================
 *
 *       Filename:  if_nameindex.c
 *
 *    Description:  return all interface's name and it's index. figure
 *		    18-20, page 400.
 *
 *        Version:  1.0
 *        Created:  03/31/2015 11:01:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unpifi.h"
#include "unproute.h"

struct if_nameindex *
if_nameindex(void)
{
	char	*buf, *next, *lim;
	size_t	len;
	struct if_msghdr *ifm;
	struct sockaddr *sa, *rti_info[RTAX_MAX];
	struct sockaddr_dl *sdl;
}
