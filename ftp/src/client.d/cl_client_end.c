/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 20:09:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/05 23:29:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

void			cl_client_end(t_client *cl)
{
	int		i;

	i = 0;
	ft_freestr(&cl->info.env.path);
	ft_freestr(&cl->info.env.home);
	while (i < NSIG)
	{
		if (cl->sig[i] != SIG_ERR)
			signal(i, cl->sig[i]);
		i++;
	}
}
