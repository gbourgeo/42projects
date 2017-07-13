/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 12:50:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/07/13 12:50:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(char *s1, char *s2)
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
