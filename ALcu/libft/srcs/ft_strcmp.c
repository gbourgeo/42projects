/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 18:39:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/01/29 13:23:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 != 0 && s2 != 0)
	{
		while ((unsigned char)s1[i] == (unsigned char)s2[i] && (s1[i] || s2[i]))
			++i;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (-1);
}
