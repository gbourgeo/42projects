/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 09:45:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 20:46:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"
#include "expansion_dollar.h"
#include "expansion_word.h"
#include "expansion_action.h"
#include "expansion_errors.h"

static void		set_new_t_exp(t_exp *newp, t_exp *param, t_ret *par)
{
	ft_memset(newp, 0, sizeof(*newp));
	newp->e = param->e;
	newp->buff = par->head + par->i;
	newp->buff_len = (param->buff + param->buff_len) - (par->head + par->i);
	newp->expand = expand_dollar_do_expansion(par);
}

static void		expand_dollar_word_free(t_ret *subs, t_exp *newp)
{
	expand_free_t_ret(subs, 0);
	free_quote(&newp->quote);
}

int				expand_dollar_word_value(t_ret *parameter, t_exp *param)
{
	static t_word	word[] = {
		WORD_NULL_SUBST, WORD_NULL_ASSIGN, WORD_NULL_ERROR,
		WORD_NONNULL_SUBST,
	};
	size_t			i;
	t_ret			subs;
	int				error;
	t_exp			newp;

	i = 0;
	ft_memset(&subs, 0, sizeof(subs));
	set_new_t_exp(&newp, param, parameter);
	if ((error = expand_loop(&subs, &newp, is_brace_end)) == ERR_NONE)
	{
		i = 0;
		while (i < sizeof(word) / sizeof(word[0]))
		{
			if (parameter->action & word[i].action)
				error = word[i].handler(&subs, parameter, param);
			i++;
		}
	}
	expand_dollar_word_free(&subs, &newp);
	return (error);
}
