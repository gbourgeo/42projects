/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 09:14:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/16 20:25:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

int				usage(char *prog_name, int caller)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(prog_name, 2);
	if (caller == SERVER)
		ft_putendl_fd(" [port] [-i] (for interactive server)", 2);
	else
		ft_putendl_fd(" [server_address] [server_port]", 2);
	return (1);
}
