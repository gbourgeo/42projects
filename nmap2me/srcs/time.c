
#include "all.h"

const char		*get_time(const char *format, struct timeval *t)
{
	static char	tbuf[128];
	struct tm	*tm;

	tm = localtime(&t->tv_sec);
	strftime(tbuf, sizeof(tbuf), format, tm);
	return (tbuf);
}
