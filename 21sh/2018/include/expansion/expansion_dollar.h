/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_dollar.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:18:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 21:57:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_DOLLAR_H
# define EXPANSION_DOLLAR_H

# include "expansion.h"

/*
** Typedef for dollar_get_parameter_init()
*/
typedef int		(*t_end)(t_exp *);

typedef struct	s_dollar
{
	int			(*check)(int);
	int			(*handler)(t_ret *, t_exp *);
}				t_dollar;

int				expand_dollar_do_expansion(t_ret *parameter);
int				expand_dollar_get_action(t_ret *ret, t_exp *param);
int				expand_dollar_parameter(t_exp *param, t_ret *ret);
int				expand_dollar_parameter_init(t_ret *parameter, t_exp *param);
int				expand_dollar_parameter_value(t_ret *parameter, t_exp *param);
int				expand_dollar_quote(t_exp *param, t_ret *ret);
int				expand_dollar_special(t_ret *to, t_exp *param);
int				expand_dollar_subs(t_exp *param, t_ret *ret);
int				expand_dollar_word_value(t_ret *parameter, t_exp *param);
int				expand_dollar_word(t_ret *ret, t_exp *param, char op, char cl);

#endif
