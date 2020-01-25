/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_stor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:10:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:55:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "sv_main.h"
#include "sv_struct.h"

// static int		put_buff(char **buff, long *size, t_hdr *hdr)
// {
// 	if ((*buff = malloc(hdr->size)) != NULL)
// 		*size = hdr->size;
// 	else if ((*buff = malloc(65000)) != NULL)
// 		*size = 65000;
// 	else
// 		return (ERR_MALLOC);
// 	return (IS_OK);
// }

// static int		put_receive(int fd, t_data *data, t_hdr *hdr)
// {
// 	char	*buff;
// 	long	size;
// 	int		ret;
// 	int		received;
// 	int		errnb;

// 	received = 0;
// 	if ((errnb = put_buff(&buff, &size, hdr)) != IS_OK)
// 		return (errnb);
// 	while (received < hdr->size && errnb == IS_OK)
// 	{
// 		ret = recv(data->socket, buff, size, MSG_DONTWAIT | MSG_NOSIGNAL);
// 		if (ret <= 0)
// 			errnb = sv_recv_error(ret);
// 		else if (write(fd, buff, ret) != ret)
// 			errnb = ERR_WRITE;
// 		else
// 			received += ret;
// 	}
// 	free(buff);
// 	return (errnb);
// }

// static int		put_type(int type)
// {
// 	if (type == tf_binary)
// 		return (0755);
// 	if (type == tf_ascii)
// 		return (0644);
// 	return (0);
// }

// static void		print_info_d(const char *s1, long nb, t_client *cl,
// t_server *sv)
// {
// 	if (!FT_CHECK(sv->options, sv_interactive))
// 		return ;
// 	printf("Client \x1B[33m%d\x1B[0m: %s %ld\n", cl->fd, s1, nb);
// }

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
	return (sv_response(cl, "502 %s unimplemented command", cmds[0]));
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
