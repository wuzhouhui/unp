/*
 * =============================================================================
 *
 *       Filename:  tpi_close.c
 *
 *    Description:  tpi_close() for send a ordered release to peer.
 *		    figure 31-12, page 688
 *
 *        Version:  1.0
 *        Created:  04/24/2015 02:34:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "tpi_daytime.h"

void tpi_close(int fd)
{
	struct T_ordrel_req ordrel_req;
	struct strbuf ctlbuf;

	ordrel_req.PRIM_type = T_ORDREL_REQ;

	ctlbuf.len = sizeof(struct T_ordrel_req);
	ctlbuf.buf = (char *)&ordrel_req;
	Putmsg(fd, &ctlbuf, NULL, 0);

	Close(fd);
}
