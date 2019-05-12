/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_valid_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 05:46:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 18:00:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int			is_token_valid_name(t_param *param)
{
	const char	*str;
	size_t		n;

	str = param->token->head;
	n = param->i - (size_t)(param->token->head - param->line);
	if (!n || ft_isdigit(*str))
		return (0);
	while (n--)
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		else
			str++;
	return (1);
}
