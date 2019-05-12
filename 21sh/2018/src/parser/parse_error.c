/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 11:27:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "parser.h"
#include "parser_errors.h"
#include "token.h"

static void		near_err(const char *err, t_token *token, t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	ft_dprintf(STDERR_FILENO, "%s `", err);
	if (token == NULLTOKEN || *token->head == '\n')
		write(STDERR_FILENO, "\\n", 2);
	else
		write(STDERR_FILENO, token->head, token->len);
	ft_dprintf(STDERR_FILENO, "'\n");
}

static void		non_near_err(const char *err, t_token *token, t_s_env *e)
{
	(void)token;
	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	ft_dprintf(STDERR_FILENO, "%s\n", err);
}

int				parse_error(int err, t_token *token, t_s_env *e)
{
	static t_err	errors[] = {
		{ NULL, NULL },
		{ UNEXPECTED_STR, near_err },
		{ PARAMETER_STR, near_err },
		{ HANDLED_STR, near_err },
		{ MALLOC_STR, non_near_err },
		{ SIGNAL_STR, non_near_err },
		{ QUOTE_STR, non_near_err },
	};

	errors[err].handler(errors[err].str, token, e);
	*e->ret = 2;
	return (0);
}
