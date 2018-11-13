#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/kd.h>

static int			**allocate_keys(size_t len1, size_t len2)
{
	int				**key_table;

	key_table = malloc(sizeof(*key_table) * (len1 + 1));
	if (key_table == NULL) {
		return NULL;
	}
	for (size_t i = 0; i < len1; i++)
	{
		key_table[i] = malloc(sizeof(**key_table) * len2);
		if (key_table[i] == NULL) {
			for (size_t j = 0; j < i; j++)
				free(key_table[j]);
			free(key_table);
			return NULL;
		}
	}
	key_table[len1] = NULL;
	return key_table;
}

static int			get_bind(int fd, unsigned char index, unsigned char table)
{
	struct kbentry	ke;

	ke.kb_index = index;
	ke.kb_table = table;
	if (ioctl(fd, KDGKBENT, (unsigned long)&ke)) {
//		fprintf(stderr, "KDGKBENT error at index %d in table %d\n", index, table);
		return -1;
	}
	return ke.kb_value;
}

int 				**get_keys(int fd, int nb_keys, int nb_keymap, int **keymaps)
{
	int				**key_table;

	key_table = allocate_keys(nb_keys, nb_keymap);
	if (key_table == NULL) {
		return NULL;
	}
	for (int i = 0; i < nb_keys; i++) {
		for (int j = 0; j < nb_keymap; j++) {
			key_table[i][j] = get_bind(fd, i, keymaps[1][j]);
		}
	}
	return key_table;
}
