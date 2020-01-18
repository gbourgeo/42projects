/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_retr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:09:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/18 20:24:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "sv_main.h"

static int		put_buff(char **buff, long *size, t_hdr *hdr)
{
	if ((*buff = malloc(hdr->size)) != NULL)
		*size = hdr->size;
	else if ((*buff = malloc(65000)) != NULL)
		*size = 65000;
	else
		return (ERR_MALLOC);
	return (IS_OK);
}

static int		put_receive(int fd, t_data *data, t_hdr *hdr)
{
	char	*buff;
	long	size;
	int		ret;
	int		received;
	int		errnb;

	received = 0;
	if ((errnb = put_buff(&buff, &size, hdr)) != IS_OK)
		return (errnb);
	while (received < hdr->size && errnb == IS_OK)
	{
		ret = recv(data->socket, buff, size, MSG_DONTWAIT | MSG_NOSIGNAL);
		if (ret <= 0)
			errnb = sv_recv_error(ret);
		else if (write(fd, buff, ret) != ret)
			errnb = ERR_WRITE;
		else
			received += ret;
	}
	free(buff);
	return (errnb);
}

static int		put_type(int type)
{
	if (type == tf_binary)
		return (0755);
	if (type == tf_ascii)
		return (0644);
	return (0);
}

static void		print_info_d(const char *s1, long nb, t_client *cl,
t_server *sv)
{
	if (!FT_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client \x1B[33m%d\x1B[0m: %s %ld\n", cl->fd, s1, nb);
}

int				sv_retr(t_client *cl, t_server *sv)
{
	t_hdr		hdr;
	int			fd;
	int			errnb;

	if ((errnb = sv_receive_hdr(cl->data.socket, &hdr)) != IS_OK)
		return (errnb);
	print_info_d("Header size:", hdr.size, cl, sv);
	print_info_d("Header type:", hdr.type, cl, sv);
	if (hdr.size > TRANSFERT_MAX || !put_type(hdr.type))
		return (ERR_DATA_HDR);
	errnb = O_CREAT | O_TRUNC | O_WRONLY;
	if ((fd = open(cl->data.file, errnb, put_type(hdr.type))) < 0)
		return (ERR_OPEN);
	errnb = put_receive(fd, &cl->data, &hdr);
	close(fd);
	return (errnb);
}

int				sv_retr_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Retreive file from server\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
