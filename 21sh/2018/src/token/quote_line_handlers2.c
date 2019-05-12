/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_line_handlers2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:34:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 02:06:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"

int				dbraced_line(t_param *param, t_line *line)
{
	char		*add;

	add = "";
	if (param->token->alias)
		add = " ";
	else if (!param->token->alias)
		add = "\n";
	if (!(param->line = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				parenthed_line(t_param *param, t_line *line)
{
	char		*add;

	add = "";
	if (*line->curr->buff
	&& ft_strncmp(param->token->head + param->token->len - 1, "(", 1)
	&& line->curr->buff[0] != ')')
		add = ";";
	if (!(param->line = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				dparenthed_line(t_param *param, t_line *line)
{
	char		*add;

	if (*line->curr->buff
	&& ft_strncmp(param->token->head + param->token->len - 2, "$(", 2)
	&& line->curr->buff[0] != ')')
		add = ";";
	if (!(param->line = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				backquoted_line(t_param *param, t_line *line)
{
	char		*add;

	if (*line->curr->buff && param->token->head[param->token->len - 1] != '`'
	&& line->curr->buff[0] != '`')
		add = ";";
	if (!(param->line = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}
