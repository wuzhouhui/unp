/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/20/2015 10:54:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "udpcksum.h"

/* define global variables */
struct sockaddr	*dest, *local;
struct sockaddr_in locallookup;
socklen_t destlen, locallen;

int	datalink;	/* from pcap_datalink(), in <net/bpf.h> */
char	*device;	/* pcap device */
pcap_t	*pd;		/* packet capture struct pointer */
int	rawfd;		/* raw socket to write on */
int	snaplen = 200;	/* amount of data to capture */
int	verbose;
int	zerosum;	/* send UDP query with no checksum. */

static void usage(const char *);

int main(int argc, char *argv[])
{
	int	c, lopt = 0;
	char	*ptr, localname[1024], *localport;
	struct addrinfo *aip;

	opterr = 0;
	while ((c = getopt(argc, argv, "0i:l:v")) != -1) {
		switch (c) {
		case '0':
			zerosum = 1;
			break;
		case 'i':
			device = optarg;	/* pcap device */
			break;
		case 'l':	/* local IP address and port #: a.b.c.d.p */
			if ((ptr = strrchr(optarg, '.')) == NULL)
				usage("invalid -l option");

			*ptr++ = 0;	/* null replace final period */
			localport = ptr; /* service name or port number */
			strncpy(localname, optarg, sizeof(localname));
			lopt = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		case '?':
			usage("unrecognized option");
		}
	}

	if (optind != argc - 2)
		usage("missing <host> and/or <serv>");
	/*
	 * convert destination name and service.
	 */
	aip = Host_serv(argv[optind], argv[optind + 1], AF_INET, SOCK_DGRAM);
	dest = aip->ai_addr;	/* don't freeaddrinfo() */
	destlen = aip->ai_addrlen;

	/*
	 * need local IP address for source IP address for UDP datagrams. 
	 * can't specify 0 and let IP choose, as we need to know it for 
	 * the pseudoheader to calculate the UDP checksum.
	 * if -l option supplied, then use those values; otherwise,
	 * connect a UDP socket to the destination to determine the right 
	 * source address.
	 */
	if (lopt) {
		/* convert local name and service */
		aip = Host_serv(localname, localport, AF_INET, SOCK_DGRAM);
		local = aip->ai_addr;	/* don't freeaddrinfo() */
		locallen = aip->ai_addrlen;
	} else {
		int	s;
		s = Socket(AF_INET, SOCK_DGRAM, 0);
		Connect(s, dest, destlen);
		/* kernel choose correct local address for dest */
		locallen = sizeof(locallookup);
		local = (struct sockaddr *)&locallookup;
		Getsockname(s, local, &locallen);
		if (locallookup.sin_addr.s_addr = htonl(INADDR_ANY))
			err_quit("can't determine local address - use -l\n");
		close(s);
	}

	open_output();	/* open output, either raw socket or libnet */
	open_pcap();	/* open packet capture device */
	setuid(getuid()); /* don't need superuser privileges anymore */
	Signal(SIGTERM, cleanup);
	Signal(SIGINT, cleanup);
	Signal(SIGHUP, cleanup);

	test_udp();
	cleanup(0);
}
