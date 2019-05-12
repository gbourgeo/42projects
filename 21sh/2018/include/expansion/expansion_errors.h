/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_errors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 17:39:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/16 20:58:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_ERRORS_H
# define EXPANSION_ERRORS_H

# define ERR_NONE_STR				"???"
# define ERR_SYNTAX_STR				"bad substitution."
# define ERR_MODIFIER_STR			"unrecognized modifier."
# define ERR_UNHANDLED_STR			"pattern not handled yet."
# define ERR_MALLOC_STR				"malloc error."
# define ERR_NO_ENV_STR				"variable not set."
# define ERR_DIRECTORY_STACK_STR	"not enough directory stack entries."
# define ERR_GIVEN_STR				""
# define ERR_NO_SUCH_USER_STR		"no such user or named directory:"
# define ERR_AMBIGUOUS_STR			"ambiguous redirect."
# define ERR_PIPE_STR				"pipe failed."
# define ERR_FCNTL_STR				"fcntl failed."
# define ERR_FORK_STR				"fork failed."
# define ERR_NO_MATCH_FOUND_STR		"no matches found"

/*
** Enumeration of expansions errors
*/
enum
{
	ERR_NONE = 0,
	ERR_SYNTAX,
	ERR_MODIFIER,
	ERR_UNHANDLED,
	ERR_MALLOC,
	ERR_NO_ENV,
	ERR_DIRECTORY_STACK,
	ERR_GIVEN,
	ERR_NO_SUCH_USER,
	ERR_AMBIGUOUS,
	ERR_PIPE,
	ERR_FCNTL,
	ERR_FORK,
	ERR_NO_MATCH_FOUND
};

# define ERR_NONE_FUNC				{ ERR_NONE            , err_none_func }
# define ERR_SYNTAX_FUNC			{ ERR_SYNTAX          , err_syntax_func }
# define ERR_MODIFIER_FUNC			{ ERR_MODIFIER        , err_modifier_func }
# define ERR_UNHANDLED_FUNC			{ ERR_UNHANDLED       , err_unhandled_func }
# define ERR_MALLOC_FUNC			{ ERR_MALLOC          , err_malloc_func }
# define ERR_NO_ENV_FUNC			{ ERR_NO_ENV          , err_no_env_func }
# define ERR_DIRECTORY_STACK_FUNC	{ ERR_DIRECTORY_STACK , err_directory_func }
# define ERR_GIVEN_FUNC				{ ERR_GIVEN           , err_given_func }
# define ERR_NO_SUCH_USER_FUNC		{ ERR_NO_SUCH_USER    , err_no_user_func }
# define ERR_AMBIGUOUS_FUNC			{ ERR_AMBIGUOUS       , err_ambigous_func }
# define ERR_PIPE_FUNC				{ ERR_PIPE            , err_pipe_func }
# define ERR_FCNTL_FUNC				{ ERR_FCNTL           , err_fcntl_func }
# define ERR_FORK_FUNC				{ ERR_FORK            , err_fork_func }
# define ERR_NO_MATCH_FUNC			{ ERR_NO_MATCH_FOUND  , err_no_match_func }

typedef struct	s_error
{
	int			error;
	void		(*handler)(t_ret *, t_exp *);
}				t_error;

void			err_none_func(t_ret *ret, t_exp *par);
void			err_syntax_func(t_ret *ret, t_exp *par);
void			err_modifier_func(t_ret *ret, t_exp *par);
void			err_unhandled_func(t_ret *ret, t_exp *par);
void			err_malloc_func(t_ret *ret, t_exp *par);
void			err_no_env_func(t_ret *ret, t_exp *par);
void			err_directory_func(t_ret *ret, t_exp *par);
void			err_given_func(t_ret *ret, t_exp *par);
void			err_no_user_func(t_ret *ret, t_exp *par);
void			err_ambigous_func(t_ret *ret, t_exp *par);
void			err_pipe_func(t_ret *ret, t_exp *par);
void			err_fcntl_func(t_ret *ret, t_exp *par);
void			err_fork_func(t_ret *ret, t_exp *par);
void			err_no_match_func(t_ret *ret, t_exp *par);

#endif
