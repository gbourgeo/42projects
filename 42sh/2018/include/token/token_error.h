/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 04:08:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 19:37:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_ERROR_H
# define TOKEN_ERROR_H

# include "token.h"

enum
{
	ERR_FREE_ALL = -1,
	ERR_NONE = 0,
	ERR_MALLOC,
	ERR_MATCHING_EOF,
	ERR_HEREDOC_EOF,
};

# define ERR_MALLOC_STR		"allocating memory failed"
# define ERR_MATCHING_STR	"unexpected EOF while looking for matching"
# define ERR_HEREDOC_STR	"warning: here-document delimited by end-of-file"

# define ERR_MALLOC_FUNC	{ err_malloc, ERR_MALLOC_STR }
# define ERR_MATCHING_FUNC	{ err_matching, ERR_MATCHING_STR }
# define ERR_HEREDOC_FUNC	{ err_heredoc, ERR_HEREDOC_STR }

typedef struct	s_error
{
	void		(*handler)(t_param *, const char *);
	const char	*str;
}				t_error;

#endif
