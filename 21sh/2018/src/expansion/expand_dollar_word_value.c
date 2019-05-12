/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 09:45:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 20:40:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"
#include "expansion_dollar.h"
#include "expansion_word.h"
#include "expansion_action.h"
#include "expansion_errors.h"

int				word_small_suffix(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)subs;
	(void)para;
	(void)param;
	return (0);
}

int				word_large_suffix(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)subs;
	(void)para;
	(void)param;
	return (0);
}

int				word_small_prefix(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)subs;
	(void)para;
	(void)param;
	return (0);
}

int				word_large_prefix(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)subs;
	(void)para;
	(void)param;
	return (0);
}

int				expand_dollar_word_value(t_ret *parameter, t_exp *param)
{
	static t_word	word[] = {
		WORD_SMALL_SUFFIX, WORD_LARGE_SUFFIX, WORD_SMALL_PREFIX,
		WORD_LARGE_PREFIX, WORD_NULL_SUBST, WORD_NULL_ASSIGN, WORD_NULL_ERROR,
		WORD_NONNULL_SUBST,
	};
	size_t			i;
	t_ret			subs;
	int				error;

	i = 0;
	ft_memset(&subs, 0, sizeof(subs));
	param->expand = expand_dollar_do_expansion(parameter);
	if ((error = expand_loop(&subs, param, is_brace_end)) == ERR_NONE)
	{
		++param->i;
		while (i < sizeof(word) / sizeof(word[0]))
		{
			if (parameter->action & word[i].action)
				error = word[i].handler(&subs, parameter, param);
			i++;
		}
	}
	expand_free_t_ret(&subs, 0);
	return (error);
}
