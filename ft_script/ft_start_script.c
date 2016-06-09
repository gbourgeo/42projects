/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_script.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 02:37:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 02:55:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			ft_start_script(t_env *e)
{
	if (e->opt[opt_q] == 0)
	{
		ft_putstr("Script started, output file is ");
		ft_putendl(e->file);
		ft_putstr_fd("Script started on ", e->fd);
		gettimeofday(&e->time, NULL);
		ft_putstr_fd(ctime(&e->time.tv_sec), e->fd);
	}
	if (ft_fork(e))
		return (1);
	if (e->opt[opt_q] == 0)
	{
		ft_putstr("\nScript done, output file is ");
		ft_putendl(e->file);
		ft_putstr_fd("\nScript done on ", e->fd);
		gettimeofday(&e->time, NULL);
		ft_putstr_fd(ctime(&e->time.tv_sec), e->fd);
	}
	return (0);
}
