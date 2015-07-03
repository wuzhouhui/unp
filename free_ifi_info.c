/*
 * =============================================================================
 *
 *       Filename:  free_ifi_info.c
 *
 *    Description:  free space get by get_ifi_info.
 *
 *        Version:  1.0
 *        Created:  03/27/2015 03:41:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unpifi.h"

void free_ifi_info(struct ifi_info *ifihead)
{
	struct ifi_info *ifi, *ifinext;

	for (ifi = ifihead; ifi; ifi = ifinext) {
		if (ifi->ifi_addr)
			free(ifi->ifi_addr);
		if (ifi->ifi_brdaddr)
			free(ifi->ifi_brdaddr);
		if (ifi->ifi_dstaddr)
			free(ifi->ifi_dstaddr);
		ifinext = ifi->ifi_next;
		free(ifi);
	}
}
