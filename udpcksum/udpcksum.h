/*
 * =============================================================================
 *
 *       Filename:  udpcksum.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/20/2015 10:49:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */
#include "unp.h"
#include <pcap.h>

#include <netinet/in_systm.h>	/* required for ip.h */
#include <netinet/in.h>
#include <netinet/ip.h>
/* #include <netinet/ip_var.h> */
#include <netinet/udp.h>
/* #include <netinet/udp_var.h> */
#include <net/if.h>
#include <netinet/if_ether.h>

#define TTL_OUT	64	/* outgoing TTL */

/* globals */
extern struct sockaddr *dest, *local;
extern socklen_t destlen, locallen;
extern int datalink;
extern char *device;
extern pcap_t *pd;
extern int rawfd;
extern int snaplen;
extern int verbose;
extern int zerosum;

/* function prototype */
void cleanup(int);
char *next_pcap(int *);
void open_output(void);
void open_pcap(void);
void send_dns_query(void);
void test_udp(void);
void udp_write(char *, int);
struct udpiphdr *udp_read(void);
