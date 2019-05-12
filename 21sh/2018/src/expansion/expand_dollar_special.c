/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_special.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 23:02:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 19:42:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_special.h"
#include "expansion_errors.h"
#include "expansion_dollar.h"

int				special_error(int error, char *save)
{
	free(save);
	return (error);
}

int				expand_dollar_special(t_ret *para, t_exp *param)
{
	static t_special	special[] = {
		{ '@', special_argv }, { '*', special_argvs }, { '?', special_return },
		{ '-', special_option }, { '$', special_pid }, { '!', special_jobs },
		{ '#', special_argc },
	};
	size_t				i;
	char				*word;

	i = 0;
	word = &para->word[para->i--];
	if (word[1] && !ft_strchr("}:-=?+#%", word[1]))
		return (ERR_SYNTAX);
	while (i < sizeof(special) / sizeof(special[0]))
	{
		if (word[0] == special[i].value)
			return (special[i].handler(para, param));
		i++;
	}
	return (ERR_NONE);
}

int				special_argc(t_ret *para, t_exp *param)
{
	t_ret		sub;
	char		*nbr;
	int			error;

	ft_memset(&sub, 0, sizeof(sub));
	if (param->e->filein)
		nbr = ft_itoa(param->e->ac - 1);
	else
		nbr = ft_itoa(param->e->ac - 1);
	error = param_addstr(nbr, &sub);
	if (nbr)
		free(nbr);
	if (error)
		return (special_error(error, sub.word));
	if (!para->word[para->i])
		para->hash = 0;
	para->freeable = 1;
	para->substitute = sub.word;
	return (ERR_NONE);
}

int				special_argv(t_ret *para, t_exp *param)
{
	t_ret		sub;
	size_t		j;
	int			qtype;

	ft_memset(&sub, 0, sizeof(sub));
	j = (param->e->filein) ? 2 : 1;
	qtype = quote_type(param->quote);
	while (param->e->av[j])
	{
		if (param_addstr(param->e->av[j], &sub))
			return (special_error(ERR_MALLOC, sub.word));
		j++;
		if (param->e->av[j])
			if ((qtype == DOUBLE_QUOTE && param_addstr("\" \"", &sub))
			|| (qtype != DOUBLE_QUOTE && param_addchar(' ', &sub)))
				return (special_error(ERR_MALLOC, sub.word));
	}
	para->freeable = 1;
	para->substitute = sub.word;
	return (ERR_NONE);
}

int				special_argvs(t_ret *para, t_exp *param)
{
	t_ret		sub;
	size_t		j;

	ft_memset(&sub, 0, sizeof(sub));
	j = (param->e->filein) ? 2 : 1;
	while (param->e->av[j])
	{
		if (param_addstr(param->e->av[j], &sub)
			|| (param->e->av[j + 1]
				&& param_addchar(' ', &sub)))
			return (special_error(ERR_MALLOC, sub.word));
		j++;
	}
	para->freeable = 1;
	para->substitute = sub.word;
	return (ERR_NONE);
}
