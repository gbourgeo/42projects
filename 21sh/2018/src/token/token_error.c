/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 04:07:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 18:01:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "token.h"
#include "token_error.h"

static char		get_delimiter(int type)
{
	if (type == BACKSLASH)
		return ('\\');
	if (type == DOUBLE_QUOTE)
		return ('"');
	if (type == SINGLE_QUOTE)
		return ('\'');
	if (type == BRACE || type == D_BRACE)
		return ('}');
	if (type == PARENTHESE || type == D_PARENTHESE)
		return (')');
	if (type == BACKQUOTE)
		return ('`');
	return ('?');
}

static void		err_malloc(t_param *param, const char *str)
{
	ft_dprintf(STDERR_FILENO, "%s: ", param->e->progname);
	if (param->e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", param->e->filein);
	ft_dprintf(STDERR_FILENO, "%s\n", str);
	*param->e->ret = 2;
}

static void		err_matching(t_param *param, const char *str)
{
	t_quote		*quote;

	quote = quote_get(param->token->quote);
	ft_dprintf(STDERR_FILENO, "%s: ", param->e->progname);
	if (param->e->filein && quote)
		ft_dprintf(STDERR_FILENO, "line %ld: ", quote->line);
	ft_dprintf(STDERR_FILENO, "%s `%c'\n", str, get_delimiter(quote->type));
	*param->e->ret = 2;
}

static void		err_heredoc(t_param *param, const char *str)
{
	t_token		*eof;
	char		*wanted;

	eof = (param->hdoc) ? ((t_token *)param->hdoc->token)->next : NULLTOKEN;
	wanted = (eof) ? ft_strndup((char *)eof->head, eof->len) : NULL;
	ft_dprintf(STDERR_FILENO, "%s: ", param->e->progname);
	if (param->e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", param->e->filein);
	ft_dprintf(STDERR_FILENO, "%s (wanted `%s')\n", str, wanted);
	ft_strdel(&wanted);
	*param->e->ret = 0;
}

t_token			*token_error(int err, t_param *param)
{
	static t_error	errors[] = {
		{ NULL, NULL }, ERR_MALLOC_FUNC, ERR_MATCHING_FUNC, ERR_HEREDOC_FUNC,
	};

	if (err > ERR_NONE)
		errors[err].handler(param, errors[err].str);
	if (err != ERR_HEREDOC_EOF)
	{
		free_token(&param->head);
		free_hdoc(&param->hdoc);
	}
	return (NULLTOKEN);
}
