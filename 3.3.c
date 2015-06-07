#include <arpa/inet.h>
#include <string.h>

int inet_pton_loose(int family, const char *strptr, void *addrptr)
{
	int	ret;
	struct in_addr in_addr;

	switch (family) {
	case AF_INET:
		if ((ret = inet_pton(family, strptr, addrptr)))
			return(ret);

		/* ret == 0 */
		return(inet_aton(strptr, (struct in_addr *)addrptr));

	case AF_INET6:
		if ((ret = inet_pton(family, strptr, addrptr)))
			return(ret);

		/* ret == 0 */
		if (!(ret = inet_aton(strptr, &in_addr)))
			return(ret);

		/* valid */
		memset(addrptr, 0x00, sizeof(struct in6_addr));
		((struct in6_addr *)addrptr)->s6_addr[10] = 0xff;
		((struct in6_addr *)addrptr)->s6_addr[11] = 0xff;
		memcpy(addrptr + 12, &in_addr, 4);
		return(1);

	default:
		return(-1);
	}
}
