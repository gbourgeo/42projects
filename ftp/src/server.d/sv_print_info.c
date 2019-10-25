/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 23:11:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/24 23:25:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void		sv_print_info(t_server *sv)
{
	ft_putstr("\x1B[4mHome\x1B[0m:\t\"\x1B[32m");
	ft_putstr(sv->info.env.home);
	ft_putstr("\x1B[0m\"\n");
	ft_putstr("\x1B[4mPath\x1B[0m:\t\"\x1B[32m");
	ft_putstr(sv->info.env.path);
	ft_putstr("\x1B[0m\"\n");
	ft_putstr("\x1B[4mBuff Size\x1B[0m:\t\x1B[0m");
	ft_putnbr(BUFF_SIZE);
	ft_putstr("\n");
	ft_putstr("\x1B[4mData Size\x1B[0m:\t\x1B[0m");
	ft_putnbr(DATA_SIZE);
	ft_putstr("\n");
	ft_putstr("\x1B[4mMax Clients\x1B[0m:\t\x1B[0m");
	ft_putnbr(CLIENTS_MAX);
	ft_putstr("\n");
	ft_putendl("\x1B[33mSERVEUR: Waiting for clients...\x1B[0m");
}
