/*
 * =============================================================================
 *
 *       Filename:  sctp_check_notify.c
 *
 *    Description:  notification check function. figure 23-11, page 499.
 *
 *        Version:  1.0
 *        Created:  04/06/2015 10:02:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

void check_notification(int sock_fd, char *recvline, int rd_len)
{
	union sctp_notification *snp;
	struct sctp_assoc_change *sac;
	struct sockaddr_storage *sa1, *sar;
	int	num_rem, num_loc;

	snp = (union sctp_notification *)recvline;
	if (snp->sn_header.sn_type == SCTP_ASSOC_CHANGE) {
		sac = &snp->sn_assoc_change;
		if ((sac->sac_state == SCTP_ASSOC_CHANGE) ||
				(sac->sac_state == SCTP_RESTART)) {
			num_rem = sctp_getpaddrs(sock_fd, sac->sac_assoc_id,
					&sar);
			printf("There are %d remote addresses and they"
			       " are: \n", num_rem);
			sctp_print_addresses(sar, num_rem);
			sctp_freepaddrs(sar);

			num_loc = sctp_getladdrs(sock_fd, sac->sac_assoc_id,
					&sal);
			printf("There are %d local addresses and they are: \n",
					num_loc);
			sctp_print_addresses(sal, num_loc);
			sctp_freepaddrs(sal);
		}
	}
}
