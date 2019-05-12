/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:05:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 02:20:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static int		define_token(int c)
{
	if (!c || (ft_isspace(c)) || c == '#')
		return (UNDEFINED);
	if (ft_isoperator(c))
		return (OPERATOR);
	return (TOKEN);
}

t_token			*new_token(char *buff, size_t pos)
{
	t_token		*new;

	new = ft_memalloc(sizeof(*new));
	if (!new)
		return (NULLTOKEN);
	new->type = define_token(buff[pos]);
	new->head = buff + pos;
	return (new);
}
