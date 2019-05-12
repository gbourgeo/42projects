/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 10:27:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:51:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_dollar.h"
#include "expansion_errors.h"

static void		expand_dollar_quoted(char *quote, char c)
{
	if (*quote == 0)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

int				expand_dollar_word(t_ret *ret, t_exp *param, char op, char cl)
{
	int			depth;
	char		quote;
	char		c;

	depth = 0;
	quote = 0;
	c = param->buff[param->i];
	while (c != cl || depth || quote)
	{
		if (c == '"')
			expand_dollar_quoted(&quote, '"');
		else if (c == '\'')
			expand_dollar_quoted(&quote, '\'');
		else if (c == '\\')
			++param->i;
		else if (c == op && !quote)
			++depth;
		else if (c == cl && !quote)
			--depth;
		if (param_addchar(c, ret))
			return (ERR_MALLOC);
		++param->i;
		c = param->buff[param->i];
	}
	return (ERR_NONE);
}
