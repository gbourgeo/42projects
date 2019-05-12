/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word_null_subst.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:59:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 19:44:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_action.h"
#include "expansion_errors.h"
#include "expansion_word.h"

int				word_null_subst(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)param;
	if (para->substitute && para->substitute[0])
		return (ERR_NONE);
	if (!(para->action & COLON_ACTION) && para->substitute)
		return (ERR_NONE);
	para->substitute = subs->word;
	para->freeable = 1;
	if (subs->substitute)
		free(subs->substitute);
	ft_memset(subs, 0, sizeof(*subs));
	return (ERR_NONE);
}
