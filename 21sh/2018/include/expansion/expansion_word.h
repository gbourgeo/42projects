/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_word.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 01:49:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/08 16:52:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_WORD_H
# define EXPANSION_WORD_H

# include "expansion.h"

# define WORD_SMALL_SUFFIX	{ REMOVE_SMALLEST_SUFFIX_PATTERN, word_small_suffix}
# define WORD_LARGE_SUFFIX	{ REMOVE_LARGEST_SUFFIX_PATTERN, word_large_suffix }
# define WORD_SMALL_PREFIX	{ REMOVE_SMALLEST_PREFIX_PATTERN, word_small_prefix}
# define WORD_LARGE_PREFIX	{ REMOVE_LARGEST_PREFIX_PATTERN, word_large_prefix }
# define WORD_NULL_SUBST	{ ACT_NULL_SUBST, word_null_subst }
# define WORD_NULL_ASSIGN	{ ACT_NULL_ASSIGN, word_null_assign }
# define WORD_NULL_ERROR	{ ACT_NULL_ERROR, word_null_error }
# define WORD_NONNULL_SUBST	{ ACT_NONNULL_SUBST, word_nonnull_subst }

typedef struct	s_word
{
	int			action;
	int			(*handler)(t_ret *, t_ret *, t_exp *);
}				t_word;

int				word_small_suffix(t_ret *subs, t_ret *para, t_exp *param);
int				word_large_suffix(t_ret *subs, t_ret *para, t_exp *param);
int				word_small_prefix(t_ret *subs, t_ret *para, t_exp *param);
int				word_large_prefix(t_ret *subs, t_ret *para, t_exp *param);
int				word_null_subst(t_ret *subs, t_ret *para, t_exp *param);
int				word_null_assign(t_ret *subs, t_ret *para, t_exp *param);
int				word_null_error(t_ret *subs, t_ret *para, t_exp *param);
int				word_nonnull_subst(t_ret *subs, t_ret *para, t_exp *param);

#endif
