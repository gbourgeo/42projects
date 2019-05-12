/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word_null_error.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 19:00:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 21:37:05 by gbourgeo         ###   ########.fr       */
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
	if (param->e->filein)
		param->e->shell_loop = 0;
	if (para->freeable)
		free(para->substitute);
	if (!(para->substitute = subs->word) || !para->substitute[0])
		para->substitute = "parameter null or not set";
	else
		para->freeable = 1;
	subs->word = NULL;
	return (ERR_GIVEN);
}
