/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word_null_error.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 19:00:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:51:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_word.h"
#include "expansion_errors.h"
#include "expansion_action.h"

int				word_null_error(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)param;
	if (para->substitute && para->substitute[0])
		return (ERR_NONE);
	if (!(para->action & COLON_ACTION) && para->substitute)
		return (ERR_NONE);
	if (param_addstr(": ", para))
		return (ERR_MALLOC);
	if ((subs->substitute && subs->substitute[0])
	|| (subs->word && subs->word[0]))
	{
		if (param_addstr(subs->word, para))
			return (ERR_MALLOC);
	}
	else if (param_addstr("parameter not set", para))
		return (ERR_MALLOC);
	para->substitute = para->word + para->brace + para->hash + 1;
	return (ERR_GIVEN);
}
