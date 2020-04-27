
#include "all.h"
#include "ft_printf.h"

#include <sys/socket.h>
#include <unistd.h>

int				init_socket(unsigned char protocol)
{
	int				fd;
	int				on;

	fd = socket(AF_INET, SOCK_RAW, protocol);
	if (fd < 0)
	{
		ft_printf("ERROR: socket() failed.");
		return (-1);
	}
	on = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0)
	{
		ft_printf("ERROR: setsockopt() failed to set IP_HDRINCL.");
		close(fd);
		return (-1);
	}
	on = 1;
	if (setsockopt(fd, SOL_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
	{
		ft_printf("ERROR: setsockopt() failed to set IP_HDRINCL.");
		close(fd);
		return (-1);
	}
	on = 0;
	if (setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, &on, sizeof(on)) < 0)
	{
		ft_printf("ERROR: setsockopt() failed to set IP_HDRINCL.");
		close(fd);
		return (-1);
	}
	// if (setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, &g_global.ifr, sizeof(g_global.ifr)) < 0)
	// {
	// 	ft_printf("ERROR: setsockopt() failed to set SO_BINDTODEVICE.");
	// 	close(fd);
	// 	return (-1);
	// }
	return (fd);
}
