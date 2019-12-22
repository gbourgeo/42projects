/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 23:11:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 00:49:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void	sv_print_path(char *path)
{
	char	**split;
	int		i;

	i = 0;
	printf(COLOR_UNDERLINED"Path"COLOR_RESET":\t\t");
	if ((split = ft_strsplit(path, ':')))
		while (split[i])
		{
			printf("\""COLOR_YELLOW"%s"COLOR_RESET"\"\n", split[i++]);
			if (split[i])
				printf("\t\t");
		}
	ft_tabdel(&split);
}

static void	sv_print_users(t_user *user, t_server *sv)
{
	printf(COLOR_UNDERLINED"Users"COLOR_RESET":"
	"\t\tType\t| Name\t\t| Pass\t\t| Right\t| Home\n\t\t");
	if (user)
		while (user)
		{
			printf("%s\t  "COLOR_ITALIC""COLOR_GREEN"%s"COLOR_RESET"\t%s  "
			COLOR_DARK""COLOR_ITALIC""COLOR_GREY"%s"COLOR_RESET"\t%s  "
			COLOR_YELLOW"%d"COLOR_RESET"\t "COLOR_BLUE"%s"COLOR_RESET"\n",
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
		printf(COLOR_RED"Empty"COLOR_RESET);
	printf("\n");
}

void		sv_server_info(t_server *sv)
{
	printf(COLOR_UNDERLINED"IPv4"COLOR_RESET"\t\t"COLOR_UNDERLINED);
	printf("%s\n"COLOR_RESET,
	(sv->ip[sv_v4] > 0) ? COLOR_GREEN"ONLINE" : COLOR_RED"OFFLINE");
	printf(COLOR_UNDERLINED"IPv6"COLOR_RESET"\t\t"COLOR_UNDERLINED);
	printf("%s\n"COLOR_RESET,
	(sv->ip[sv_v6] > 0) ? COLOR_GREEN"ONLINE" : COLOR_RED"OFFLINE");
	printf(COLOR_UNDERLINED"Home"COLOR_RESET":\t\t\""COLOR_BOLD);
	printf(COLOR_PINK"%s"COLOR_RESET"\"\n", sv->info.env.home);
	sv_print_path(sv->info.env.path);
	printf(COLOR_UNDERLINED"Buff Size"COLOR_RESET":\t"COLOR_RESET"%d\n",
	CMD_BUFF_SIZE);
	printf(COLOR_UNDERLINED"Data Size"COLOR_RESET":\t"COLOR_RESET"%d\n",
	DATA_BUFF_SIZE);
	printf(COLOR_UNDERLINED"Max Clients"COLOR_RESET":\t"COLOR_RESET"%d\n",
	CLIENTS_MAX);
	sv_print_users(sv->users, sv);
	printf(COLOR_LIGHT_BLUE"Server Online..."COLOR_RESET"\n");
}
