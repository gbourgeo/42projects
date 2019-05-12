/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_line_handlers1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:16:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 02:04:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"

int				aliased_line(t_param *param, t_line *line)
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

int				bslashed_line(t_param *param, t_line *line)
{
	((char *)param->line)[ft_strlen(param->line) - 1] = '\0';
	param->token->len--;
	if (!(param->line = ft_strjoin(param->line, line->curr->buff)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				dquoted_line(t_param *param, t_line *line)
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

int				squoted_line(t_param *param, t_line *line)
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

int				braced_line(t_param *param, t_line *line)
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
