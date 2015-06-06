/*
 * =============================================================================
 *
 *       Filename:  web.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/26/2015 06:25:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "web.h"

int main(int argc, char **argv)
{
	int	i, fd, n, maxnconn, flags, error;
	char	buf[MAXLINE];
	fd_set	rs, ws;

	if (argc < 5)
		err_quit("usage: web <#conns> <hostname> <homepage> <file1> ...");
	maxnconn = atoi(argv[1]);

	nfiles = min(argc - 4, MAXFILES);
	for (i = 0; i < nfiles; i++) {
		file[i].f_name	= argv[i + 4];
		file[i].f_host	= argv[2];
		file[i].f_flags	= 0;
	}
	printf("nfiles = %d\n", nfiles);
	home_page(argv[2], argv[3]);
	FD_ZERO(&rset);
	FD_ZERO(&wset);
	maxfd = -1;
	nlefttoconn = nlefttoread = nfiles;
	nconn = 0;

	while (nlefttoread > 0) {
		while (nconn < maxnconn && nlefttoconn > 0) {
			for (i = 0; i < nfiles; i++)
				if (file[i].f_flags == 0)
					break;
			if (i == nfiles)
				err_quit("nlefttoconn = %d but nothing"
					 " found", nlefttoconn);
			start_connect(&file[i]);
			nconn++;
			nlefttoconn--;
		}

		rs = rset;
		ws = wset;
		if ((n = select(maxfd + 1, &rs, &ws, NULL, NULL)) < 0)
			err_sys("select error");
		for (i = 0; i < nfiles; i++) {
			flags = file[i].f_flags;
			if (flags = 0 || flags & F_DONE)
				continue;

			fd = file[i].f_fd;
			if (flags & F_CONNECTIONG 
					&& (FD_ISSET(fd, &rs) || FD_ISSET(fd, &ws))) {
				n = sizeof(error);
				if (getsockopt(fd, SOL_SOCKET, SO_ERROR,
						&error, &n) < 0
						|| error != 0) {
					err_ret("nonblocking connect failed for %s",
							file[i].f_name);
				}

				/* connection established */
				printf("connection established for %s\n",
						file[i].f_name);
				FD_CLR(fd, &wset);
				write_get_cmd(&file[i]);
			} else if (flags & F_READING && FD_ISSET(fd, &rs)) {
				if ((n = read(fd, buf, sizeof(buf))) < 0)
					err_ret("read error for %s\n",
							file[i].f_name);

				if (n == 0) {
					printf("end-of-file on %s\n", file[i].f_name);
					close(fd);
					file[i].f_flags = F_DONE;
					FD_CLR(fd, &rset);
					nconn--;
					nlefttoread--;
				} else {
					printf("read %d bytes from %s\n",
							n, file[i].f_name);
				}
			}
		}
	}
	exit(0);
}
