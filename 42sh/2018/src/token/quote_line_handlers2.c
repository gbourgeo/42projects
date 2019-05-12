/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_line_handlers2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:34:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/24 15:46:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"

int				dbraced_line(t_param *param, t_line *line)
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

int				parenthed_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = "";
	if (*line->curr->buff
	&& ft_strncmp(param->token->head + param->token->len - 1, "(", 1)
	&& line->curr->buff[0] != ')')
		add = ";";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	param->i--;
	return (ERR_NONE);
}

int				dparenthed_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = "";
	if (*line->curr->buff
	&& ft_strncmp(param->token->head + param->token->len - 2, "$(", 2)
	&& line->curr->buff[0] != ')')
		add = ";";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	param->i--;
	return (ERR_NONE);
}

int				backquoted_line(t_param *param, t_line *line)
{
	char		*add;
	char		*newl;

	add = "";
	if (*line->curr->buff && param->token->head[param->token->len - 1] != '`'
	&& line->curr->buff[0] != '`')
		add = ";";
	if (!(newl = ft_strjoin(add, line->curr->buff)))
		return (ERR_MALLOC);
	if (!(param->line = ft_strjoinfree(param->line, newl, 3)))
		return (ERR_MALLOC);
	param->i--;
	return (ERR_NONE);
}

int				heredoc_line(t_param *param, t_line *line)
{
	t_token		*operator;
	t_token		*eof;
	char		**newl;

	operator = (t_token *)param->hdoc->token;
	eof = operator->next;
	newl = (char **)&operator->hdocline;
	param->i--;
	if (ft_strlen(line->curr->buff) == eof->len
	&& !ft_strncmp(eof->head, line->curr->buff, eof->len))
	{
		hdoc_remove(&param->hdoc);
		return (ERR_NONE);
	}
	if (!*newl)
		*newl = ft_strdup(line->curr->buff);
	else
	{
		*newl = ft_strjoinfree(*newl, "\n", 1);
		*newl = ft_strjoinfree(*newl, line->curr->buff, 1);
	}
	operator->hdoclen = ft_strlen(*newl);
	operator->hdocfree = 1;
	return (ERR_NONE);
}
