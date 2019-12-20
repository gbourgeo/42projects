/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_params_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:21:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 19:29:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_param_four(const char **arg, int *i, t_server *sv)
{
	(void)arg;
	(void)i;
	sv->options |= (1 << sv_v4);
	sv->options &= ~(1 << sv_v6);
	return (IS_OK);
}

int				sv_param_six(const char **arg, int *i, t_server *sv)
{
	(void)arg;
	(void)i;
	sv->options |= (1 << sv_v6);
	sv->options &= ~(1 << sv_v4);
	return (IS_OK);
}

int				sv_param_h(const char **arg, int *i, t_server *sv)
{
	(void)arg;
	(void)i;
	(void)sv;
	return (ERR_HELP);
}

int				sv_param_i(const char **arg, int *i, t_server *sv)
{
	(void)arg;
	(void)i;
	sv->options |= (1 << sv_interactive);
	return (IS_OK);
}

int				sv_param_u(const char **arg, int *i, t_server *sv)
{
	(void)arg;
	(void)i;
	sv->options |= (1 << sv_user_mode);
	return (IS_OK);
}
