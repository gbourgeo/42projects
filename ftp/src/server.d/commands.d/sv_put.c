/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:09:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 01:33:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "sv_main.h"

static void		print_info_s(const char *s1, const char *s2, t_client *cl,
t_server *sv)
{
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client \x1B[33m%d\x1B[0m: %s '%s'\n", cl->fd, s1, s2);
}

static void		print_info_d(const char *s1, long nb, t_client *cl,
t_server *sv)
{
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client \x1B[33m%d\x1B[0m: %s %ld\n", cl->fd, s1, nb);
}

static int		put_receive(t_data *data, t_hdr *hdr)
{
	char	*buff;
	long	size;
	int		ret;
	int		received;
	int		errnb;

	errnb = IS_OK;
	if ((buff = malloc(hdr->size)) != NULL)
		size = hdr->size;
	else if ((buff = malloc(65000)) != NULL)
		size = 65000;
	else
		return (ERR_MALLOC);
	received = 0;
	while (received < hdr->size && errnb == IS_OK)
	{
		ret = recv(data->socket, buff, size, MSG_DONTWAIT | MSG_NOSIGNAL);
		if (ret <= 0)
		{
			errnb = sv_recv_error(ret);
			continue ;
		}
		if (write(data->filefd, buff, ret) != ret)
			errnb = ERR_WRITE;
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

int				sv_put(t_client *cl, t_server *sv)
{
	t_hdr		hdr;
	int			errnb;

	print_info_s("Ready to receive file", cl->data.file, cl, sv);
	if ((errnb = sv_receive_hdr(cl->data.socket, &hdr)) != IS_OK)
		return (errnb);
	print_info_d("Header size:", hdr.size, cl, sv);
	print_info_d("Header type:", hdr.type, cl, sv);
	if (hdr.size > TRANSFERT_MAX || !put_type(hdr.type))
		return (ERR_DATA_HDR);
	if ((cl->data.filefd = open(cl->data.file,
		O_CREAT | O_TRUNC | O_WRONLY, put_type(hdr.type))) < 0)
		return (ERR_OPEN);
	if (errnb == IS_OK)
		errnb = put_receive(&cl->data, &hdr);
	close(cl->data.filefd);
	return (errnb);
}
