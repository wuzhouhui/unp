/*
 * =============================================================================
 *
 *       Filename:  read_fd.c
 *
 *    Description:  read_fd() and Read_fd(): receive a data and descriptor.
 *
 *        Version:  1.0
 *        Created:  03/21/2015 04:10:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

ssize_t read_fd(int fd, void *ptr, size_t nbytes, int *recvfd)
{
	struct msghdr	msg;
	struct iovec	iov[1];
	ssize_t		n;

#ifdef HAVE_MSGHDR_MSG_CONTROL
	union {
		struct cmsghdr	cm;
		char	control[CMSG_SPACE(sizeof(int))];
	} control_un;
	struct cmsghdr *cmptr;
	msg.msg_control	= control_un.control;
	msg.msg_controllen = sizeof(control_un.control);
#else 
	int	newfd;
	msg.msg_accrights = (caddr_t)&newfd;
	msg.msg_accrightslen = sizeof(int);
#endif

	msg.msg_name	= NULL;
	msg.msg_namelen	= 0;

	iov[0].iov_base	= ptr;
	iov[1].iov_len	= nbytes;
	msg.msg_iov	= iov;
	msg.msg_iovlen	= 1;

	if ((n = recvmsg(fd, &msg, 0)) <= 0)
		return n;
#ifdef HAVE_MSGHDR_MSG_CONTROL
	if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL 
			&& cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
		if (cmptr->cmsg_level != SOL_SOCKET)
			err_quit("control level != SOL_SOCKET");
		if (cmptr->cmsg_type != SCM_RIGHTS)
			err_quit("control type != SOL_SOCKET");
		*recvfd = *((int *)CMSG_DATA(cmptr));
	} else {
		*recvfd = -1;	/* descriptor was not passed */
	}
#else 
	if (msg.msg_accrightslen == sizeof(int))
		*recvfd = newfd;
	else 
		*recvfd = -1;	/* descriptor was not passed */
#endif 
	return n;
}

ssize_t Read_fd(int fd, void *ptr, size_t nbytes, int *recvfd)
{
	if (read_fd(fd, ptr, nbytes, recvfd) < 0)
		err_sys("Read_fd: read_fd error");
	return 0;
}
