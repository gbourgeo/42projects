/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 02:11:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 02:13:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_iswhitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 11))
		return (1);
	return (0);
}
