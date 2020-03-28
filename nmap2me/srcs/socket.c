
#include "all.h"
#include "ft_printf.h"

#include <sys/socket.h>
#include <unistd.h>

int				init_socket(unsigned char protocol, int timeout)
{
	int				fd;
	int				on;
	struct timeval	t;

	fd = socket(AF_INET, SOCK_RAW, protocol);
	if (fd < 0)
	{
		ft_printf("ERROR: socket() failed.");
		return (-1);
	}
	on = 1;
	if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
	{
		ft_printf("ERROR: setsockopt() failed to set IP_HDRINCL.");
		close(fd);
		return (-1);
	}
	on = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0)
	{
		ft_printf("ERROR: setsockopt() failed to set SO_BROADCAST.");
		close(fd);
		return (-1);
	}
	t.tv_sec = timeout / 1000;
	t.tv_usec = timeout % 1000;
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(t)) < 0)
	{
		ft_printf("ERROR: setsockopt() failed to set SO_RCVTIMEO.");
		close(fd);
		return (-1);
	}
	return (fd);
}
