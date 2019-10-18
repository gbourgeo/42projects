/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:08:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/18 03:42:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_check_params(char **path, t_client *cl, t_server *sv)
{
	char		*ptr;
	char		*tmp;

	ptr = *path;
	if (ptr && ptr[0] == '-')
		return (IS_OK);
	if (ptr[0] == '/')
	{
		if (!(ptr = ft_strjoin(sv->info.env.home, ptr)))
			return (ERR_MALLOC);
	}
	else
	{
		if (!(ptr = ft_strjoin(sv->info.env.home, cl->pwd)))
			return (ERR_MALLOC);
	}
	i = ft_strlen(ptr) - 1;
	while (i)
	{
		j = i;
		while (ptr[j])
	}
	return (IS_OK);
}
