/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:33:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/05 19:41:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_TILDE_H
# define EXPANSION_TILDE_H

# include "expansion.h"

# define TILDE_NONE		{ tilde_no_param, expand_tilde_env }
# define TILDE_PLUS		{ tilde_plus    , expand_tilde_plus }
# define TILDE_MINUS	{ tilde_minus   , expand_tilde_minus }
# define TILDE_ALPHA	{ tilde_alpha   , expand_tilde_user }

typedef struct	s_tilde
{
	int			(*comparaison)(const char *);
	int			(*handler)(t_ret *, t_ret *, t_exp *);
}				t_tilde;

int				tilde_no_param(const char *word);
int				tilde_plus(const char *word);
int				tilde_minus(const char *word);
int				tilde_digit(const char *word);
int				tilde_alpha(const char *word);

int				expand_tilde_env(t_ret *ret, t_ret *parame, t_exp *param);
int				expand_tilde_plus(t_ret *ret, t_ret *parame, t_exp *param);
int				expand_tilde_minus(t_ret *ret, t_ret *parame, t_exp *param);
int				expand_tilde_user(t_ret *ret, t_ret *parame, t_exp *param);
int				expand_tilde_not(t_ret *ret, const char *word);

#endif
