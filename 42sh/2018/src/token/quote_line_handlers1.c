/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_line_handlers1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:16:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/24 14:19:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"

int				aliased_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = (param->token->oldhd) ? " " : "\n";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				bslashed_line(t_param *param, t_line *line)
{
	((char *)param->line)[ft_strlen(param->line) - 1] = '\0';
	if ((param->token->oldhd && --param->token->oldlen <= 0)
	|| (!param->token->oldhd && --param->token->len <= 0))
		param->token->type = UNDEFINED;
	param->i -= 2;
	quote_remove(&param->token->quote, BACKSLASH);
	if (!(param->line = ft_strjoinfree(param->line, line->curr->buff, 1)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				dquoted_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = (param->token->oldhd) ? " " : "\n";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	param->i--;
	return (ERR_NONE);
}

int				squoted_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = (param->token->oldhd) ? " " : "\n";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	param->i--;
	return (ERR_NONE);
}

int				braced_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = (param->token->oldhd) ? " " : "\n";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	param->i--;
	return (ERR_NONE);
}
