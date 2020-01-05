/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:10:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/05 22:29:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "sv_main.h"

static int	get_send(char *data, size_t size, int fd)
{
	size_t	sent;
	int		ret;
	int		errnb;

	errnb = IS_OK;
	sent = 0;
	while (sent < size)
		if ((ret = send(fd, data + sent, size - sent,
		MSG_DONTWAIT | MSG_NOSIGNAL)) <= 0)
		{
			if ((errnb = sv_send_error(ret)) != IS_OK)
				return (errnb);
		}
		else
			sent += ret;
	return (errnb);
}

static int	get_file(char *file, void **map, t_hdr *hdr)
{
	struct stat	buf;
	int			fd;
	int			errnb;

	errnb = IS_OK;
	*map = MAP_FAILED;
	ft_memset(hdr, -1, sizeof(*hdr));
	if ((fd = open(file, O_RDONLY)) < 0)
		return (ERR_OPEN);
	if (fstat(fd, &buf) < 0)
		errnb = ERR_FSTAT;
	else if (!S_ISREG(buf.st_mode))
		errnb = ERR_NOT_REGULAR_FILE;
	else if ((hdr->size = lseek(fd, 0, SEEK_END)) < 0
	|| lseek(fd, 0, SEEK_SET) < 0)
		errnb = ERR_LSEEK;
	else if ((*map = mmap(NULL, hdr->size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
		errnb = ERR_MMAP;
	else
		hdr->type = (S_IXUSR & buf.st_mode) ? tf_binary : tf_ascii;
	ft_close(&fd);
	return (errnb);
}

int			sv_get(t_client *cl, t_server *sv)
{
	t_hdr	hdr;
	void	*file;
	char	*info;
	int		errnb;

	if ((errnb = sv_check_path(&cl->data.file, cl)) != IS_OK
	|| (errnb = get_file(cl->data.file, &file, &hdr)) != IS_OK)
		return (errnb);
	if (FT_CHECK(sv->options, sv_interactive))
		printf("Client "COLOR_YELLOW"%d"COLOR_RESET": Sending file '%s', %ld "
		"bytes, type %d\n", cl->fd, cl->data.file, hdr.size, hdr.type);
	info = (char *)&hdr;
	if ((errnb = get_send(info, sizeof(hdr), cl->data.socket)) == IS_OK)
		errnb = get_send(file, hdr.size, cl->data.socket);
	munmap(file, hdr.size);
	return (errnb);
}
