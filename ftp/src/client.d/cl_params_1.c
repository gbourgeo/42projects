/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_params_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 22:59:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/08 14:45:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_param_i(char **av, int *i, t_client *cl)
{
	(void)av;
	(void)i;
	cl->options |= (1 << cl_interactive);
	return (IS_OK);
}

int				cl_param_h(char **av, int *i, t_client *cl)
{
	(void)av;
	(void)i;
	(void)cl;
	return (ERR_HELP);
}

int				cl_param_n(char **av, int *i, t_client *cl)
{
	(void)av;
	(void)i;
	cl->options |= (1 << cl_ncurses);
	return (IS_OK);
}
