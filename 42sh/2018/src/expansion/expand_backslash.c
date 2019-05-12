/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 23:53:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:49:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_loop.h"
#include "expansion_errors.h"

int			expand_backslash(t_exp *param, t_ret *ret)
{
	int		error;

	if ((error = param_addchar(param->buff[param->i++], ret)) == ERR_NONE)
		error = param_addchar(param->buff[param->i], ret);
	return (error);
}
