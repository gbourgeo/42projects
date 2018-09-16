/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_intro.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 09:44:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/07 20:27:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

void			cl_prompt(t_envi *cl)
{
	ft_putstr("\033[0mServer:\033[32m");
	if (cl->pwd)
		ft_putstr(cl->pwd);
	else
		ft_putchar('/');
	ft_putstr(" \033[35m ");
	ft_putstr(cl->user);
	ft_putstr(":\033[33m");
	ft_putstr(cl->lpwd);
	if (cl->success)
		ft_putstr("\033[31m > \033[0m");
	else
		ft_putstr("\033[32m > \033[0m");
}
