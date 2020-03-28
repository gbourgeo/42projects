
#include "all.h"
#include "ft_printf.h"
#include "ft_vprintf.h"
#include <unistd.h>

void 			nmap_error(t_params *e, char *str, ...)
{
	va_list		ap;

	va_start(ap, 0);
	ft_printf("%s: ", e->progname);
	ft_vprintf(str, ap);
	write(1, "\n", 1);
	va_end(ap);
	free_params(e);
	exit(1);
}