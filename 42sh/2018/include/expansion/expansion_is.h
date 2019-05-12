/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_is.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 00:19:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 18:09:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_IS_H
# define EXPANSION_IS_H

# include "expansion.h"

int				is_brace_end(t_exp *param);
int				is_valid_name(int c);
int				is_special(int c);
int				is_expand_null(t_ret *ret);

#endif
