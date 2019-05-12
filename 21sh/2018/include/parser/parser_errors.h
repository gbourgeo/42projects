/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:35:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 19:54:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

# include "token.h"

enum
{
	ERR_NONE = 0,
	ERR_UNEXPECTED_TOKEN,
	ERR_MISSING_PARAMETER,
	ERR_NOT_HANDLED_YET,
	ERR_MALLOC_FAILED,
	ERR_SIGNAL,
	ERR_QUOTE
};

# define UNEXPECTED_STR		"syntax error near unexpected token"
# define PARAMETER_STR		"syntax error: missing token"
# define HANDLED_STR		"syntax error near unhandled token"
# define MALLOC_STR			"syntax error: malloc failed"
# define SIGNAL_STR			"syntax error: signal failed"
# define QUOTE_STR			"syntax error: unexpected end of file"

typedef struct	s_error
{
	const char	*str;
	void		(*handler)(const char *, t_token *, t_s_env *);
}				t_err;

#endif
