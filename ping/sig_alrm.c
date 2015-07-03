/*
 * =============================================================================
 *
 *       Filename:  sig_alrm.c
 *
 *    Description:  SIGALRM handler, figure 28-13, page 594.
 *
 *        Version:  1.0
 *        Created:  04/14/2015 09:44:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "ping.h"

void sig_alrm(int signo)
{
	(*pr->fsend)();

	alarm(1);
	return;
}
