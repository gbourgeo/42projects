/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_retr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:09:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 16:37:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "sv_main.h"
#include "sv_struct.h"

static int		sv_retr_sendfile(char *data, size_t size, int fd)
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

static int		sv_retr_getfile(char *file, void **map, t_hdr *hdr)
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
	// else
	// 	hdr->type = cl->data.type;
	ft_close(&fd);
	return (errnb);
}

/*
** RETR
** 125, 150
**   (110)
**   226, 250
**   425, 426, 451
** 450, 550
** 500, 501, 421, 530
*/

int				sv_retr(char **cmds, t_client *cl)
{
	t_hdr		hdr;
	void		*file;
	int			errnb;

	if (!cmds[1] || !cmds[1][0] || !sv_validpathname(cmds[1]))
		return (sv_response(cl, "501 %s",
		ft_get_error((cmds[1]) ? ERR_INVALID_PARAM : ERR_NB_PARAMS)));
	// Verification du chemin / fichier
	if ((errnb = sv_check_path(&cmds[1], cl)) != IS_OK)
	{
		sv_response(cl, "451 internal error");
		return (errnb);
	}
	// Ouverture du canal de données
	if (cl->data.fd <= 0)
		return (sv_response(cl, "425 connection not established"));
	if ((errnb = sv_response(cl, "125 ready for transfert")) == IS_OK
	// Verification de fichier
	&& (errnb = sv_check_path(&cmds[1], cl)) == IS_OK
	&& (errnb = sv_retr_getfile(cmds[1], &file, &hdr)) == IS_OK
	&& (errnb = sv_retr_sendfile((char *)&hdr, sizeof(hdr), cl->data.socket)) == IS_OK)
		errnb = sv_retr_sendfile(file, hdr.size, cl->data.socket);
	return (errnb);
}

/*
** RETR <SP> <pathname> <CRLF>
*/

int				sv_retr_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes the server-DTP to transfer a copy of the",
		"file, specified in the pathname, to the server- or user-DTP",
		"at the other end of the data connection.  The status and",
		"contents of the file at the server site shall be unaffected.",
		NULL
	};

	return (sv_print_help(cl, cmd, "<pathname>", help));
}
