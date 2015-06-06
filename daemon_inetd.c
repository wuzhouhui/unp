/*
 * =============================================================================
 *
 *       Filename:  daemon_inetd.c
 *
 *    Description:  function daemon_inetd: daemonizing the process ran by 
 *		    inetd.
 *
 *        Version:  1.0
 *        Created:  03/16/2015 09:21:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"
#include <syslog.h>

extern int daemon_proc;	/* defined in error.c */

void daemon_inetd(const char *pname, int facility)
{
	daemon_proc = 1;
	openlog(pname, LOG_PID, facility);
}
