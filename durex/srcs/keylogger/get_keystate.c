#ifdef X11
# include <X11/XKBlib.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#ifdef X11
int			get_keystate(int keybit, int socket)
{
  Display	*display;
  char		*monitor;
  unsigned	state;

//	monitor = getenv("DISPLAY");
	monitor = ":0";
	display = XOpenDisplay(monitor);
	if (!display) {
		dprintf(socket, "Can't get display to find Lockers states.\n");
		return 0;
	}
	if (XkbGetIndicatorState(display, XkbUseCoreKbd, &state) != Success) {
		dprintf(socket, "Can't get indicator state for Lockers.\n");
	}
	XCloseDisplay(display);
	return (state & keybit);
}
#else
int			get_keystate(int keybit, int socket)
{
	int		fd;
	char	state;

	fd = open("/dev/console", O_WRONLY);
	if (fd < 0) {
		dprintf(socket, "Can't open /dev/console.\n");
		return 0;
	}
	state = LED_CAP;
	if (ioctl(fd, KDGKBLED, &state)) {
		dprintf(socket, "ioctl: %s\n", strerror(errno));
		return 0;
	}
	dprintf(socket, "state is %d\n", state);
	return (state & keybit);
}
#endif
