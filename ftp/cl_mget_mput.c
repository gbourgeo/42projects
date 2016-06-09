/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_mget_mput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/05 15:10:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/06 07:29:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int			cl_mget_mput(char **cmd, t_envi *cl)
{
	int		i;
	char	*swap[3];

	i = 1;
	if (!cmd[1])
		return (file_error("ERROR: No arguments given.", cl, CLIENT, 0));
	swap[0] = &cmd[0][1];
	swap[2] = NULL;
	cl->rec = 0;
	while (cmd[i] && cl->rec == 0)
	{
		swap[1] = cmd[i];
		ft_strcpy(cl->buff, swap[0]);
		ft_strcat(cl->buff, " ");
		ft_strcat(cl->buff, cmd[i]);
		cl->rec = (swap[0][0] == 'g') ? cl_get(swap, cl) : cl_put(swap, cl);
		i++;
	}
	return (cl->rec);
}
