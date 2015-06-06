/*
 * =============================================================================
 *
 *       Filename:  calloc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/15/2015 02:03:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include <stdlib.h>

void *Calloc(size_t nuemb, size_t size)
{
	void *ptr = NULL;

	if ((ptr = calloc(nuemb, size)) == NULL)
		err_sys("calloc error");
	return(ptr);
}
