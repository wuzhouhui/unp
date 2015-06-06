/*
 * =============================================================================
 *
 *       Filename:  sig_alrm.c
 *
 *    Description:  sig_alrm() function, figure 28-23, page 605.
 *
 *        Version:  1.0
 *        Created:  04/16/2015 02:22:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "trace.h"

int	gotalarm;

void sig_alrm(int signo)
{
	gotalarm = 1;
	return;
}
