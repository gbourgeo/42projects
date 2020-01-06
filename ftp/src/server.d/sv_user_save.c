/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 01:08:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/06 18:11:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "sv_main.h"

static void		print_info(const char *s1, const char *s2, t_client *cl,
t_server *sv)
{
	if (!FT_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client "FTP_YELLOW"%d"FTP_RESET": %s `%s`\n", cl->fd, s1, s2);
}

static void		get_info(char *info, t_user *user)
{
	ft_strcpy(info, (user->type & us_server) ? "S:" : "C:");
	ft_strcat(info, user->name);
	ft_strcat(info, ":");
	ft_strcat(info, user->pass);
	ft_strcat(info, ":");
	if (user->rights <= 0)
		ft_strcat(info, "0:\n");
	if (user->rights == 1)
		ft_strcat(info, "1:\n");
	if (user->rights == 2)
		ft_strcat(info, "2:\n");
	if (user->rights >= 3)
		ft_strcat(info, "3:\n");
}

int				sv_save_user(t_user *user, t_client *cl, t_server *sv)
{
	int		fd;
	char	info[1024];
	ssize_t	ret;

	fd = open(SV_USERS_FILE, O_WRONLY | O_APPEND);
	if (fd < 0)
	{
		print_info("Failed to open", SV_USERS_FILE, cl, sv);
		return (ERR_OPEN);
	}
	get_info(info, user);
	ret = write(fd, info, ft_strlen(info));
	close(fd);
	if (ret != (ssize_t)ft_strlen(info))
	{
		print_info("Failed to write to", SV_USERS_FILE, cl, sv);
		return (ERR_WRITE);
	}
	print_info("Successfully added", user->name, cl, sv);
	return (IS_OK);
}
