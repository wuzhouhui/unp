/*
 * =============================================================================
 *
 *       Filename:  web01.c
 *
 *    Description:  web client using thread. figure 26-13, page 549.
 *
 *        Version:  1.0
 *        Created:  04/10/2015 12:36:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unpthread.h"
#include <thread.h>	/* solaris threads */

#define MAXFILES	20 
#define SERV		"80"	/* port number or service name. */

struct file {
	char	*f_name;	/* filename. */
	char	*f_host;	/* hostname or IP address */
	int	f_fd;		/* descriptor. */
	int	f_flags;	/* F_xxx below. */
	pthread_t f_tid;	/* thread ID. */
} file[MAXFILES];
#define F_CONNECTION	1	/* connect() in progress. */
#define F_READING	2	/* connect() complete; now reading */
#define F_DONE		4	/* all done */

#define GET_CMD		"GET %s HTTP/1.0\r\n\r\n"

int	nconn, nfiles, nlefttoconn, nlefttoread;

void	*do_get_read(void *);
void	home_page(const char *, const char *);
void	write_get_cmd(struct file *);

int main(int argc, char **argv)
{
	int	i, n, maxnconn;
	pthread_t tid;
	struct file *fptr;

	if (argc < 5)
		err_quit("usage: web <#conns> <IPaddr> <homepace> file ...");
	maxnconn = atoi(argv[1]);

	nfiles = min(argc - 4, MAXFILES);
	for (i = 0; i < nfiles; i++) {
		file[i].f_name	= argv[i + 4];
		file[i].f_host	= argv[2];
		file[i].f_flags	= 0;
	}
	printf("nfiles = %d\n", nfiles);
	home_page(argv[2], argv[3]);
	nlefttoconn = nlefttoread = nfiles;
	nconn = 0;

	while (nlefttoread > 0) {
		while (nconn < maxnconn && nlefttoconn > 0) {
			/* find a file to read */
			for (i = 0; i < nfiles; i++)
				if (file[i].f_flags == 0)
					break;
			if (i == nfiles)
				err_quit("nlefttoconn = %d, but nothing to found", nlefttoconn);

			file[i].f_flags = F_CONNECTION;
			Pthread_create(&tid, NULL, &do_get_read, &file[i]);
			file[i].f_tid = tid;
			nconn++;
			nlefttoconn--;
		}

		if ((n = thr_join(0, &tid, (void **)&fptr)) != 0)
			errno = n, err_sys("thr_join error");

		nconn--;
		nlefttoread--;
		printf("thread id %d for %s done\n", tid, fptr->f_name);
	}

	exit(0);
}

void *do_get_read(void *vptr)
{
	int	fd, n;
	char	line[MAXLINE];
	struct file *fptr;

	fptr = (struct file *)vptr;

	fd = Tcp_connect(fptr->f_host, SERV);
	fptr->f_fd = fd;
	printf("do_get_read for %s, fd %d, thread %d\n",
			fptr->f_name, fd, fptr->f_tid);
	write_get_cmd(fptr);	/* write() the GET command. */
	/*
	 * read server's reply.
	 */
	for ( ; ; ) {
		if ((n = Read(fd, line, MAXLINE)) == 0)
			break;	/* server closeed connection. */
		printf("read %d bytes from %s\n", n, fptr->f_name);
	}
	printf("end-of-file on %s\n", fptr->f_name);
	Close(fd);
	fptr->f_flags = F_DONE;	/* clear F_READING */

	return(fptr);	/* terminate thread. */
}
