/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 15:58:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/06 18:38:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_control_c(t_env *e)
{
	ft_bzero(e->history->command, CMD_SIZE + 1);
	treat_command(e);
}

void		ft_control_d(t_env *e)
{
	ft_exit(NULL, e);
}
