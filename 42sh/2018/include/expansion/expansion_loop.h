/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_loop.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 12:15:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/08 13:48:39 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_LOOP_H
# define EXPANSION_LOOP_H

# include "expansion.h"

/*
** Structure that regroup expansions and their associated handler
*/

typedef struct	s_expansion_handler
{
	char		value;
	int			(*handler)(t_exp *, t_ret *);
}				t_e_character;

# define OP_EXP_BACKSLSH	{ '\\', expand_backslash }
# define OP_EXP_SQUOTE		{ '\'', expand_squote }
# define OP_EXP_DQUOTE		{ '"',  expand_dquote }
# define OP_EXP_DOLLAR		{ '$',  expand_dollar }
# define OP_EXP_BACKTICK	{ '`',  expand_backtick }
# define OP_EXP_TILDE		{ '~',  expand_tilde }
# define OP_EXP_GLOB		{ '*',  expand_glob }
# define OP_EXP_BRACKET		{ '[',  expand_glob }
# define OP_EXP_QUESTION	{ '?',  expand_glob }

int				expand_backslash(t_exp *param, t_ret *ret);
int				expand_dollar(t_exp *param, t_ret *ret);
int				expand_backtick(t_exp *param, t_ret *ret);
int				expand_dquote(t_exp *param, t_ret *ret);
int				expand_squote(t_exp *param, t_ret *ret);
int				expand_tilde(t_exp *param, t_ret *ret);
int				expand_glob(t_exp *param, t_ret *ret);
int				expand_math(t_exp *param, t_ret *ret);

#endif
