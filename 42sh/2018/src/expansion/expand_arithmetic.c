/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:36:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 21:02:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_errors.h"

int				expand_arithmetic(t_exp *param, t_ret *ret)
{
	(void)param;
	expand_free_t_ret(ret, 0);
	param_addstr("Arithmetic", ret);
	return (ERR_UNHANDLED);
}
