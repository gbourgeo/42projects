/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word_nonnull_subst.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 19:02:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:51:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_word.h"
#include "expansion_errors.h"
#include "expansion_action.h"

int				word_nonnull_subst(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)param;
	if (para->substitute
		&& (para->substitute[0] || !(para->action & COLON_ACTION)))
	{
		expand_free_t_ret(para, 0);
		para->word = subs->substitute;
		para->substitute = subs->word;
		para->freeable = 0;
		ft_memset(subs, 0, sizeof(*subs));
	}
	return (ERR_NONE);
}
