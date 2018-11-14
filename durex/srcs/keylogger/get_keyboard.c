#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int			filter(const struct dirent *file)
{
	char			filename[512];
	struct stat		filestat;

	snprintf(filename, sizeof(filename), "%s%s", "/dev/input/", file->d_name);
	if (stat(filename, &filestat))
		return 0;
	return S_ISCHR(filestat.st_mode);
}

char				*get_keyboard()
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

