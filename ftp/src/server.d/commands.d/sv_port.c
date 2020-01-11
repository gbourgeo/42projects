/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_port.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:30:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/11 23:25:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** DATA PORT (PORT) PORT DU CANAL DE DONNEES
** Example: PORT h1,h2,h3,h4,p1,p2
*/

static int			only_digit(char **s)
{
	int		i;
	int		j;

	i = 0;
	while (s[i])
	{
		j = 0;
		if (!ft_isdigit(s[i][j++]))
			return (0);
		i++;
	}
	return (1);
}

static void			copy_address(char *s, char **addr)
{
	int			i;

	i = 0;
	*s = 0;
	if (addr)
		while (addr[i])
		{
			ft_strcat(s, addr[i++]);
			if (addr[i])
				ft_strcat(s, ".");
		}
}

int					sv_port(char **cmds, t_client *cl, t_server *sv)
{
	char			**info;
	unsigned int	port;

	if (!cmds[1] || !cmds[1][0])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	if (!(info = ft_strsplit(cmds[1], ',')))
		return (sv_cmd_err(ft_get_error(ERR_MALLOC), cmds[0], cl, sv));
	if (ft_tablen(info) != 6 || !only_digit(info))
	{
		ft_tabdel(&info);
		return (sv_cmd_err("Wrong parameter", cmds[0], cl, sv));
	}
	copy_address(cl->login.address, info);
	port = (ft_atoi(info[4]) << 8) + (unsigned char)ft_atoi(info[5]);
	cl->login.port = ft_itoa(port);
	ft_tabdel(&info);
	return (sv_cmd_ok("Port Command Accepted", cl, sv));
}
