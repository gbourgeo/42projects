/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 23:11:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 18:09:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void	sv_print_path(char *path)
{
	char	**split;
	int		i;

	i = 0;
	printf(FTP_UNDERLINED"Path"FTP_RESET":\t\t");
	if ((split = ft_strsplit(path, ':')))
		while (split[i])
		{
			printf("\""FTP_YELLOW"%s"FTP_RESET"\"\n", split[i++]);
			if (split[i])
				printf("\t\t");
		}
	ft_tabdel(&split);
}

static void	sv_print_users(t_user *user, t_server *sv)
{
	printf(FTP_UNDERLINED"Users"FTP_RESET":"
	"\t\tType\t| Name\t\t| Pass\t\t| Right\t| Home\n\t\t");
	if (user)
		while (user)
		{
			printf("%s\t  "FTP_ITALIC""FTP_GREEN"%s"FTP_RESET"\t%s  "
			FTP_DARK""FTP_ITALIC""FTP_GREY"%s"FTP_RESET"\t%s  "
			FTP_YELLOW"%d"FTP_RESET"\t "FTP_BLUE"%s"FTP_RESET"\n",
			(user->type & us_server) ? "Server" : "Client",
			user->name,
			(ft_strlen(user->name) > 5) ? "" : "\t",
			user->pass,
			(ft_strlen(user->pass) > 5) ? "" : "\t",
			user->rights,
			&user->home[ft_strlen(sv->info.env.home) - 1]);
			if ((user = user->next))
				printf("\t\t");
		}
	else
		printf(FTP_RED"Empty"FTP_RESET);
	printf("\n");
}

void		sv_server_info(t_server *sv)
{
	printf(FTP_UNDERLINED"IPv4"FTP_RESET"\t\t"FTP_UNDERLINED);
	printf("%s"FTP_RESET" (%s)\n",
	(sv->ip[sv_v4] > 0) ? FTP_GREEN"ONLINE" : FTP_RED"OFFLINE",
	sv->addr[sv_v4]);
	printf(FTP_UNDERLINED"IPv6"FTP_RESET"\t\t"FTP_UNDERLINED);
	printf("%s"FTP_RESET" (%s)\n",
	(sv->ip[sv_v6] > 0) ? FTP_GREEN"ONLINE" : FTP_RED"OFFLINE",
	sv->addr[sv_v6]);
	printf(FTP_UNDERLINED"Home"FTP_RESET":\t\t\""FTP_BOLD);
	printf(FTP_PINK"%s"FTP_RESET"\"\n", sv->info.env.home);
	sv_print_path(sv->info.env.path);
	printf(FTP_UNDERLINED"Buff Size"FTP_RESET":\t"FTP_RESET"%d\n",
	CMD_BUFF_SIZE);
	printf(FTP_UNDERLINED"Data Size"FTP_RESET":\t"FTP_RESET"%d\n",
	DATA_BUFF_SIZE);
	printf(FTP_UNDERLINED"Max Clients"FTP_RESET":\t"FTP_RESET"%d\n",
	CLIENTS_MAX);
	sv_print_users(sv->users, sv);
	printf(FTP_LIGHT_BLUE"Server Online..."FTP_RESET"\n");
}
