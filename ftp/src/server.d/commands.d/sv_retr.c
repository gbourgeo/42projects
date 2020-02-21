/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_retr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:09:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/21 14:07:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "sv_main.h"
#include "sv_struct.h"

int				sv_retr_exec(char *opt, char **cmds, t_client *cl)
{
	ssize_t	sent;
	int		ret;
	int		errnb;

	(void)opt;
	(void)cmds;
	sent = 0;
	errnb = IS_OK;
	while (sent < cl->data.fsize)
		if ((ret = send(cl->data.socket, cl->data.file + sent,
		cl->data.fsize - sent, MSG_DONTWAIT | MSG_NOSIGNAL)) <= 0)
		{
			if ((errnb = sv_send_error(ret)) != IS_OK)
				return (errnb);
		}
		else
			sent += ret;
	return (errnb);
}

static int		sv_retr_open_file(char *file, t_data *data)
{
	struct stat	buf;
	int			fd;
	int			errnb;

	errnb = IS_OK;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (ERR_OPEN);
	if (fstat(fd, &buf) < 0)
		errnb = ERR_FSTAT;
	else if (!S_ISREG(buf.st_mode))
		errnb = ERR_NOT_REGULAR_FILE;
	else if ((data->fsize = lseek(fd, 0, SEEK_END)) < 0
	|| lseek(fd, 0, SEEK_SET) < 0)
		errnb = ERR_LSEEK;
	else if ((data->file = mmap(NULL, data->fsize, PROT_READ,
	MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		errnb = ERR_MMAP;
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
	int			errnb;

	cl->data.file = MAP_FAILED;
	cl->data.fsize = -1;
	cl->data.function = sv_retr_exec;
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 Please login with USER and PASS."));
	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (!cmds[1] || !sv_validpathname(cmds[1]) || cmds[2])
		return (sv_response(cl, "501 %s", ft_get_error(ERR_INVALID_PARAM)));
	if (!cl->data.port && cl->data.pasv_fd < 0 && cl->data.socket < 0)
		return (sv_response(cl, "425 Use PORT or PASV first"));
	if ((errnb = ft_check_path(&cmds[1], cl->pwd, cl->home)) != IS_OK
	|| (errnb = sv_retr_open_file(cmds[1], &cl->data)) != IS_OK
	|| (errnb = sv_response(cl, "125 Ready for transfert")) != IS_OK
	|| (errnb = sv_new_pid(cmds, cl, NULL)) != IS_OK)
		errnb = sv_response(cl, "451 Internal error (%s)", ft_get_error(errnb));
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
