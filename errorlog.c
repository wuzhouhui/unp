/*
 * error routines for programs than can run as a daemon
 */

#include "apue.h"
#include <errno.h>	/* for definition of errno */
#include <stdarg.h>	/* ISO C variable arguments */
#include <syslog.h>

static void log_doit(int, int, int, const char *, va_list ap);

/*
 * caller must define and set this: nonzero if
 * interactive, zero if daemon.
 */
extern int log_to_stderr;

/*
 * initialize syslog(), if running as daemon.
 */
void log_open(const char *ident, int option, int facility)
{
	if (log_to_stderr == 0)
		openlog(ident, option, facility);
}

/*
 * nonfatal error related to a system call.
 * print a message with the system's errno value and return.
 */
void log_ret(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	log_doit(1, errno, LOG_ERR, fmt, ap);
	va_end(ap);
}

/*
 * fatal error related to a sytem call.
 * print a message and terminate.
 */
void log_sys(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	log_doit(1, errno, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(2);
}

/*
 * nonfatal error unrelated to a system call.
 * print a message and return.
 */
void log_msg(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	log_doit(0, 0, LOG_ERR, fmt, ap);
	va_end(ap);
}

/*
 * fatal error unrelated to a system call.
 * print a message and terminate.
 */
void log_quit(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	log_doit(0, 0, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(2);
}

/*
 * fatal error related to a system call.
 * Error number passed as a explicit parameter.
 * print a message and terminzte.
 */
void log_exit(int error, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	log_doit(1, error, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(2);
}

/*
 * print a message and return to caller.
 * caller specifies "errnoflag" and "priority"
 */
static void log_doit(int errnoflag, int error, int priority,
		const char *fmt, va_list ap)
{
	char	buf[MAXLINE];

	vsnprintf(buf, MAXLINE - 1, fmt, ap);
	if (errnoflag)
		snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1,
				": %s", strerror(error));
	strcat(buf, "\n");
	if (log_to_stderr) {
		fflush(stdout);
		fputs(buf, stderr);
		fflush(stderr);
	} else {
		syslog(priority, "%s", buf);
	}
}
