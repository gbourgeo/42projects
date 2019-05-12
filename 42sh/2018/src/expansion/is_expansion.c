/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 05:37:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/27 18:04:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"

int				is_valid_name(int c)
{
	return ((c == '_') || ft_isalnum(c));
}

int				is_special(int c)
{
	return ((c == '@')
		|| (c == '*')
		|| (c == '?')
		|| (c == '-')
		|| (c == '$')
		|| (c == '!')
		|| (c == '#'));
}

int				is_brace_end(t_exp *param)
{
	return (param->buff[param->i] != '}');
}

int				is_expand_null(t_ret *ret)
{
	return (!ret->word || !ret->word[ret->brace + ret->hash + 1]);
}
