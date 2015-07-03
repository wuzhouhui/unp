/*
 * =============================================================================
 *
 *       Filename:  socket.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/15/2015 02:05:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include <sys/types.h>
#include <sys/socket.h>

int Socket(int domain, int type, int proto)
{
	int	fd;

	if ((fd = socket(domain, type, proto)) < 0)
		err_sys("socket error");
	return(fd);
}
