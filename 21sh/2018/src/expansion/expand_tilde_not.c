/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_not.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:16:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:57:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_tilde.h"
#include "expansion_errors.h"

int				expand_tilde_not(t_ret *ret, const char *word)
{
	if ((*word != '~' && param_addchar('~', ret)) || param_addstr(word, ret))
		return (ERR_MALLOC);
	return (ERR_NONE);
}
