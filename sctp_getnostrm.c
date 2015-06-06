#include	"unp.h"
#include <netinet/sctp.h>

int 
sctp_get_no_strms(int sock_fd,struct sockaddr *to, socklen_t tolen)
{
	int retsz;
	struct sctp_status status;
	retsz = sizeof(status);	
	bzero(&status,sizeof(status));

	status.sstat_assoc_id = sctp_address_to_associd(sock_fd,to,tolen);
	if (getsockopt(sock_fd,IPPROTO_SCTP, SCTP_STATUS,
		   &status, &retsz) < 0)
		err_sys("sctp_get_no_strms: getsockopt error");
	return(status.sstat_outstrms);
}
