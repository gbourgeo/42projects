/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 04:07:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 03:00:04 by gbourgeo         ###   ########.fr       */
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

t_token			*token_error(int err, t_param *param)
{
	static char	*errors[] = {
		NULL, "allocating memory failed",
		"unexpected EOF while looking for matching",
		"alias error near unexpected quote"
	};
	t_quote		*quote;

	if (err != ERR_FREE_ALL)
	{
		quote = quote_get(param->token->quote);
		ft_dprintf(STDERR_FILENO, "%s: ", param->e->progname);
		if (quote && quote->line)
			ft_dprintf(STDERR_FILENO, "line %ld: ", quote->line);
		ft_dprintf(STDERR_FILENO, "%s", errors[err]);
		if (err > 1 && quote)
			ft_dprintf(STDERR_FILENO, " `%c'", get_delimiter(quote->type));
		write(STDERR_FILENO, "\n", 1);
	}
	if (err != ERR_EOF)
		free_token(&param->head);
	return (NULLTOKEN);
}
