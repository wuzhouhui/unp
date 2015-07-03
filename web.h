/*
 * =============================================================================
 *
 *       Filename:  web.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/26/2015 06:22:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

#define MAXFILES	20 
#define SERV		"80"

struct file {
	char	*f_name;
	char	*f_host;
	int	f_fd;
	int	f_flags;
} file [MAXFILES];

#define F_CONNECTIONG	1
#define F_READING	2
#define	F_DONE		4

#define GET_CMD		"GET %s HTTP/1.0\r\n\r\n"

int	nconn, nfiles, nlefttoconn, nlefttoread, maxfd;
fd_set	rset, wset;

void home_page(const char *, const char *);
void start_connect(struct file *);
void write_get_cmd(struct file *);

