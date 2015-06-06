/*
 * =============================================================================
 *
 *       Filename:  write_fd.c
 *
 *    Description:  passing a descriptor through sendmsg().
 *
 *        Version:  1.0
 *        Created:  03/21/2015 04:45:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

ssize_t write_fd(int fd, void *ptr, size_t nbytes, int sendfd)
{
	struct msghdr	msg;
	struct iovec	iov[1];

#ifdef HAVE_MSGHDR_MSG_CONTROL
	union {
		struct cmsghdr cm;
		char	control[CMSG_SPACE(sizeof(int))];
	} control_un;
	struct cmsghdr *cmptr;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);
	cmptr = CMSG_FIRSTHDR(&msg);
	cmptr->cmsg_len = CMSG_LEN(sizeof(int));
	cmptr->cmsg_type = SCM_RIGHTS;
	*((int *)CMSG_DATA(cmptr)) == sendfd;
#else
	msg.msg_accrights = (caddr_t)&sendfd;
	msg.msg_accrightslen = sizeof(int);
#endif

	msg.msg_name	= NULL;
	msg.msg_namelen	= 0;

	iov[0].iov_base	= ptr;
	iov[0].iov_len	= nbytes;
	msg.msg_iov	= iov;
	msg.msg_iovlen	= 1;

	return sendmsg(fd, &msg, 0);
}
