/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/28 00:19:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/10 13:42:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_tablen(char **table)
{
	int		i;

	i = 0;
	while (table && table[i])
		i++;
	return (i);
}
