/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 23:31:28 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/22 12:20:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "globing.h"

void	ft_nstrstr(char *str, char *to_find, int *nb)
{
	char	*ptr;
	char	*tmp;

	if ((ptr = ft_strstr(str, to_find)))
	{
		tmp = ptr;
		if (ft_strlen(ptr) > ft_strlen(to_find))
		{
			if ((ptr = ft_strchr(ptr, '/')))
			{
				while (tmp && *tmp && *tmp != '/')
					if (ft_isalnum(*tmp))
						tmp = NULL;
					else
						tmp++;
				if (tmp)
					*nb += 1;
			}
			else
				return ;
			ft_nstrstr(ptr, to_find, nb);
		}
	}
}

int		ft_nslash(char *str)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			nb++;
			while (str[i] == '/')
				i++;
			if (!str[i])
				nb--;
		}
		else
			i++;
	}
	return (nb);
}
