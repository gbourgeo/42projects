/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_addstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 04:03:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/26 02:53:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"

int				param_addstr(const char *str, t_ret *ret)
{
	if (!str)
		return (ERR_NONE);
	while (*str)
	{
		if (param_addchar(*str, ret) != ERR_NONE)
			return (ERR_MALLOC);
		str++;
	}
	return (ERR_NONE);
}
