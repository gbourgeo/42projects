#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
	
static int			is_a_console(int fd)
{
	char			arg;

	arg = 0;
	return (ioctl(fd, KDGKBTYPE, &arg) == 0 && ((arg == KB_101) || (arg == KB_84)));
}

int					get_console(void)
{
	int				fd;
	char			*console[] = { "/dev/tty", "/dev/tty0", "/dev/vc/0", "/dev/console" };

	fd = -1;
	for (size_t i = 0; i < sizeof(console) / sizeof(*console); i++)
	{
		fd = open(console[i], O_RDWR);
		if (fd < 0 && errno == EACCES)
			fd = open(console[i], O_WRONLY);
		if (fd < 0 && errno == EACCES)
			fd = open(console[i], O_RDONLY);
		if (fd < 0)
			continue ;
		if (is_a_console(fd))
			break ;
		close(fd);
		fd = -1;
	}
	if (fd < 0)
		for (fd = 0; fd < 3; fd++)
			if (is_a_console(fd))
				break ;
	return fd;
}
