/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_stor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:10:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 14:04:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "sv_main.h"
#include "sv_struct.h"

int			sv_stor_exec(char *opt, char **cmds, t_client *cl)
{
	char	buff[DATA_BUFF_SIZE];
	int		ret;

	(void)opt;
	(void)cmds;
	errno = 0;
	while (1)
	{
		ret = recv(cl->data.socket, buff, sizeof(buff),
			MSG_DONTWAIT | MSG_NOSIGNAL);
		if (ret == 0 || errno == ECONNRESET || errno == EPIPE)
			break ;
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			continue ;
		if (ret < 0)
			return (ERR_RECV);
		if (write(cl->data.ffd, buff, ret) != ret)
			return (ERR_WRITE);
	}
	return (IS_OK);
}

static int	sv_stor_open_file(char *file, t_data *data)
{
	data->ffd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->ffd < 0)
		return (ERR_OPEN);
	return (IS_OK);
}

/*
** STOR
** 125, 150
**   (110)
**   226, 250
**   425, 426, 451, 551, 552
** 532, 450, 452, 553
** 500, 501, 421, 530
*/

int			sv_stor(char **cmds, t_client *cl)
{
	int		errnb;

	cl->data.ffd = -1;
	cl->data.function = sv_stor_exec;
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 Please login with USER and PASS."));
	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (!cmds[1] || !sv_validpathname(cmds[1]) || cmds[2])
		return (sv_response(cl, "501 %s", ft_get_error(ERR_INVALID_PARAM)));
	if (!cl->data.port && cl->data.pasv_fd < 0 && cl->data.socket < 0)
		return (sv_response(cl, "425 Use PORT or PASV first"));
	if ((errnb = sv_stor_open_file(cmds[1], &cl->data)) != IS_OK
	|| (errnb = sv_new_pid(cmds, cl, NULL)) != IS_OK
	|| (errnb = sv_response(cl, "125 Ready for transfert")) != IS_OK)
		errnb = sv_response(cl, "451 Internal error (%s)", ft_get_error(errnb));
	return (errnb);
}

/*
** STOR <SP> <pathname> <CRLF>
*/

int			sv_stor_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes the server-DTP to accept the data",
		"transferred via the data connection and to store the data as",
		"a file at the server site.  If the file specified in the",
		"pathname exists at the server site, then its contents shall",
		"be replaced by the data being transferred.  A new file is",
		"created at the server site if the file specified in the",
		"pathname does not already exist.", NULL
	};

	return (sv_print_help(cl, cmd, "<pathname>", help));
}
