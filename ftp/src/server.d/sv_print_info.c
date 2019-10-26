/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 23:11:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/26 00:15:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void	sv_print_path(char *path)
{
	char	**split;
	int		i;

	i = 0;
	ft_putstr("\x1B[4mPath\x1B[0m:\t\t");
	if ((split = ft_strsplit(path, ':')))
		while (split[i])
		{
			ft_putstr("\"\x1B[34m");
			ft_putstr(split[i++]);
			ft_putstr("\x1B[0m\"");
			if (split[i])
				ft_putstr("\n\t\t");
		}
	ft_putstr("\n");
}

static void	sv_print_users(t_user *user)
{
	ft_putstr("\x1B[4mRegistered\x1B[0m:\t\x1B[0m");
	if (user)
		while (user)
		{
			ft_putstr("\x1B[0;33m");
			ft_putstr(user->name);
			ft_putstr("\x1B[0m : \x1B[37m");
			ft_putstr(user->pass);
			ft_putstr("\x1B[0m");
			if ((user = user->next))
				ft_putstr("\n\t\t");
		}
	else
		ft_putstr("\x1B[31mEmpty\x1B[0m");
	ft_putstr("\n");
}

void		sv_print_info(t_server *sv)
{
	ft_putstr("\x1B[4mHome\x1B[0m:\t\t\"\x1B[1;35m");
	ft_putstr(sv->info.env.home);
	ft_putstr("\x1B[0m\"\n");
	sv_print_path(sv->info.env.path);
	ft_putstr("\x1B[4mBuff Size\x1B[0m:\t\x1B[0m");
	ft_putnbr(FTP_BUFF_SIZE);
	ft_putstr("\x1B[0m\n");
	ft_putstr("\x1B[4mData Size\x1B[0m:\t\x1B[0m");
	ft_putnbr(FTP_DATA_SIZE);
	ft_putstr("\x1B[0m\n");
	ft_putstr("\x1B[4mMax Clients\x1B[0m:\t\x1B[0m");
	ft_putnbr(CLIENTS_MAX);
	ft_putstr("\x1B[0m\n");
	sv_print_users(sv->users);
	ft_putendl("\n\x1B[36mSERVEUR: Waiting for clients...\x1B[0m");
}
