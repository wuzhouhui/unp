/*
 * =============================================================================
 *
 *       Filename:  hostent.c
 *
 *    Description:  call gethostbyname and show message returned, figure 11-3,
 *		    page 241.
 *
 *        Version:  1.0
 *        Created:  03/14/2015 10:33:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

#ifndef INET_ADDRSTRLEM
#define INET_ADDRSTRLEM 512
#endif

int main(int argc, char *argv[])
{
	char	*ptr, **pptr;
	char	str[INET_ADDRSTRLEM];
	struct	hostent *hptr;

	while (--argc > 0) {	/* must prefix '++' */
		ptr = *++argv;
		if ((hptr = gethostbyname(ptr)) == NULL) {
			err_msg("gethostbyname error for host: %s: %s",
					ptr, hstrerror(h_errno));
			continue;
		}

		printf("official hostname: %s\n", hptr->h_name);
		for (pptr = hptr->h_aliases; *pptr; pptr++)
			printf("\talias: %s\n", *pptr);

		switch (hptr->h_addrtype) {
		case AF_INET:
			for (pptr = hptr->h_addr_list; *pptr; pptr++)
				printf("\taddress: %s\n",
						inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
			break;

		default:
			err_ret("unknown address type");
			break;
		}
	}
	exit(0);
}
