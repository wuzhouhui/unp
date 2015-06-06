/*
 * =============================================================================
 *
 *       Filename:  sigchldwaitpid.c
 *
 *    Description:  sigchldwaitpid function.
 *
 *        Version:  1.0
 *        Created:  2015年03月04日 07时20分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void sig_chld(int signo)
{
	pid_t	pid;
	int	stat;

	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);

	return;
}
