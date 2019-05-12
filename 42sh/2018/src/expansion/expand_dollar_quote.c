/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:42:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/18 15:27:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_dollar.h"
#include "expansion_errors.h"

static int		is_dquote_end(t_exp *param)
{
	return (param->buff[param->i] != '"');
}

static int		expand_dollar_dquote(t_exp *param, t_ret *ret)
{
	t_ret		subs;
	int			expand;
	int			error;

	ft_memset(&subs, 0, sizeof(subs));
	expand = param->expand;
	param->expand = 0;
	if ((error = expand_loop(&subs, param, is_dquote_end)) == ERR_NONE)
		if ((error = param_addstr(subs.word, ret)) == ERR_NONE)
			error = param_addchar(param->buff[param->i], ret);
	param->expand = expand;
	expand_free_t_ret(&subs, 0);
	return (error);
}

static int		expand_escaped_character(t_exp *param, t_ret *ret)
{
	static char	table[] = {
		0x07, 0x08, 0x00, 0x00, 0x1B, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x0A, 0x0A, 0x0A, 0x0A, 0x0D, 0x0A, 0x09, 0x00, 0x0B, 0x00, 0x00,
		0x00, 0x00,
	};
	char		c;

	if (param->buff[param->i + 1] >= 'a' && param->buff[param->i + 1] <= 'z'
	&& (c = table[(int)param->buff[param->i + 1] - 'a']))
	{
		if (param_addchar(c, ret) != ERR_NONE)
			return (ERR_MALLOC);
		else
			param->i++;
	}
	else if (param_addchar(param->buff[param->i], ret) != ERR_NONE)
		return (ERR_MALLOC);
	param->i++;
	return (ERR_NONE);
}

static int		expand_dollar_squote(t_exp *param, t_ret *ret)
{
	while (param->buff[param->i] != '\'')
		if (param->buff[param->i] == '\\')
		{
			if (expand_escaped_character(param, ret) != ERR_NONE)
				return (ERR_MALLOC);
		}
		else if (param_addchar(param->buff[param->i], ret))
			return (ERR_MALLOC);
		else
			param->i++;
	if (param_addchar(param->buff[param->i], ret))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				expand_dollar_quote(t_exp *param, t_ret *ret)
{
	if (param_addchar(param->buff[++param->i], ret) != ERR_NONE)
		return (ERR_MALLOC);
	if (param->buff[param->i++] == '"')
		return (expand_dollar_dquote(param, ret));
	return (expand_dollar_squote(param, ret));
}
