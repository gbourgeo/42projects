#include "all.h"
#include "libft.h"
#include <unistd.h>
#include <stdarg.h>

void 			nmap_error(char *str, ...)
{
	va_list		ap;
	char 		*tail;

	tail = str;
	va_start(ap, 0);
	while(*tail)
	{
		if (*tail == '%')
		{
			if (tail != str)
				write(STDERR_FILENO, str, tail - str);
			tail++;
			if (*tail == 's') {
				char *out = va_arg(ap, char*);
				write(STDERR_FILENO, out, ft_strlen(out));
			} else
			if (*tail == 'd') {
				int 	out = va_arg(ap, int);
				char 	*conv = ft_itoa(out);
				write(STDERR_FILENO, conv, ft_strlen(conv));
				free(conv);
			}
			str = tail + 1;
		}
		tail++;
	}
	if (tail != str)
		write(STDERR_FILENO, str, tail - str);
	write(STDERR_FILENO, "\n", 1);
	va_end(ap);
	if (globals.flags)
		free(globals.flags);
	if (globals.addresses) {
		for (int i = 0; globals.addresses[i]; i++)
			free(globals.addresses[i]);
		free(globals.addresses);
	}
	if (globals.threads) {
		for (int i = 0; globals.threads[i]; i++)
			free(globals.threads[i]);
		free(globals.threads);
	}
	exit(1);
}