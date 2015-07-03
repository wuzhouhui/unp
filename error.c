#include "unp.h"
#include <stdarg.h>	/* ANSI C header file */
#include <syslog.h>	/* for syslog */

int daemon_proc = 0;	/* set nonzero by daemon_init() */

static void err_doit(int, int, const char *, va_list);

/*
 * nonfatal error related to system call,
 * print message and return.
 */
void err_ret(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(1, LOG_INFO, fmt, ap);
	va_end(ap);
	return;
}

/*
 * fatal error related to system call,
 * print message and terminate.
 */
void err_sys(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * fatal error related to system call,
 * print message, dump core, and terminate.
 */
void err_dump(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	abort();
	exit(1);
}

/*
 * nonfatal error unrelated to system call,
 * print message and return.
 */
void err_msg(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(0, LOG_INFO, fmt, ap);
	va_end(ap);
	return;
}

/*
 * fatal error unrelated to system call,
 * print message and terminate.
 */
void err_quit(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(0, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * print messag and return to caller,
 * caller specifies "errnoflag" and "level"
 */
static void err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
	int	errno_save, n;
	char	buf[MAXLINE + 1];

	errno_save = errno;
#ifdef HAVE_VSNPRINTF
	vsnprintf(buf, MAXLINE, fmt, ap);	/* save */
#else
	vsprintf(buf, fmt, ap);			/* not save */
#endif
	n = strlen(buf);
	if (errnoflag)
		snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
	strcat(buf, "\n");

	if (daemon_proc) {
		syslog(level, buf);
	} else {
		fflush(stdout);	/* in case stdout and stderr are the same */
		fputs(buf, stderr);
		fflush(stderr);
	}
	return;
}
