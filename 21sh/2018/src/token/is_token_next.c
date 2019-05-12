/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:22:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/01 20:15:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int			ft_isname(int c)
{
	return (((c >= 0x07) && (c <= 0x0D))
			|| ((c >= 0x20) && (c <= 0x7E)));
}

int			ft_isnewline(int c)
{
	return ((c == '\n'));
}

int			ft_isnull(int c)
{
	return ((c == 0));
}

int			ft_isword(int c)
{
	return ((c >= 0x21) && (c <= 0x7E));
}
