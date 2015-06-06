/*
 * =============================================================================
 *
 *       Filename:  ntp.h
 *
 *    Description:  NTP format and definition. figure 21-20, page 457.
 *
 *        Version:  1.0
 *        Created:  04/04/2015 12:10:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#define JAN_1970	2208988800UL	/* 1970-1900 in seconds */

struct l_fixedpt {
	uint32_t int_part;
	uint32_t fraction;
};

struct s_fixedpt {
	uint16_t int_part;
	uint16_t fraction;
};

struct ntpdata {
	u_char	status;
	u_char	stratum;
	u_char	ppoll;
	int	precision: 8;
	struct s_fixedpt distance;
	struct s_fixedpt dispersion;
	uint32_t refid;
	struct l_fixedpt reftime;
	struct l_fixedpt org;
	struct l_fixedpt rec;
	struct l_fixedpt xmt;
};

#define VERSION_MASK	0x38
#define MODE_MASK	0x07
#define MODE_CLIENT	3
#define MODE_SERVER	4
#define	MODE_BROADCAST	5
