#include <X11/XKBlib.h>
#include <stdlib.h>
#include <stdio.h>

int				get_keystate(int keybit, int socket)
{
	Display		*display;
	char		*monitor;
	unsigned	state;

//	monitor = getenv("DISPLAY");
	state = 0;
	monitor = ":0.0";
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
