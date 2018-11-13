#include <X11/XKBlib.h>
#include <stdlib.h>
#include <stdio.h>

int					get_keystate(int keybit)
{
  Display		*display;
  char			*monitor;
  unsigned	state;

	monitor = getenv("DISPLAY");
	display = XOpenDisplay((monitor) ? monitor : ":0");
	if (!display)
		return printf("Can't get display to find Lockers states.\n");
	if (XkbGetIndicatorState(display, XkbUseCoreKbd, &state) != Success)
		return printf("Can't get indicator state for Lockers.\n");
	return (state & keybit);
}
