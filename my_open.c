/*
 * =============================================================================
 *
 *       Filename:  my_open.c
 *
 *    Description:  open a file and return its descriptor, -1 on error.
 *
 *        Version:  1.0
 *        Created:  03/21/2015 03:48:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int my_open(const char *pathname, int mode)
{
	int	fd, sockfd[2], status;
	pid_t	pid;
	char	c, argsockfd[10], argmode[10];

	if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd) < 0) {
		err_ret("my_open: socketpair error");
		return -1;
	}
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) { /* child */
		close(sockfd[0]);
		snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
		snprintf(argmode, sizeof(argmode), "%d", mode);
		execl("./openfile", "openfile", argsockfd, pathname,
				argmode, (char *)NULL);
		err_sys("execl error");
	}

	/* parent */
	close(sockfd[1]);
	if (waitpid(pid, &status, 0) < 0)
		err_sys("waitpid error");
	if (WIFEXITED(status) == 0)
		err_quit("child did not terminate");
	if ((status = WEXITSTATUS(status)) == 0) {
		Read_fd(sockfd[0], &c, 1, &fd);
	} else {
		errno = status;
		fd = -1;
	}
	close(sockfd[0]);
	return fd;
}
