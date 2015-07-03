/*
 * =============================================================================
 *
 *       Filename:  sock_ntop.c
 *
 *    Description:  sock_ntop function
 *
 *        Version:  1.0
 *        Created:  03/03/2015 10:19:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

char *sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
	char	portstr[8];
	static char str[128];

	switch (sa->sa_family) {
	case AF_INET: {
		      struct sockaddr_in *sin = (struct sockaddr_in *)sa;
		      if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str))
				      == NULL)
			      return NULL;
		      if (ntohs(sin->sin_port) != 0) {
			      snprintf(portstr, sizeof(portstr), ":%d", 
					      ntohs(sin->sin_port));
			      strcat(str, portstr);
		      }
		      return str;
	      }
	}
	return NULL;
}
