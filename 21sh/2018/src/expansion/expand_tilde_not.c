/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_not.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:16:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 14:31:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_tilde.h"
#include "expansion_errors.h"

int				expand_tilde_not(t_ret *ret, const char *word)
{
	expand_free_t_ret(ret, 0);
	if (param_addchar('~', ret) || param_addstr(word, ret))
		return (ERR_MALLOC);
	return (ERR_NONE);
}
