/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_port.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:30:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:54:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		copy_address(char *s, char **addr)
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

/*
** PORT
** 200
** 500, 501, 421, 530
*/

int				sv_port(char **cmds, t_client *cl)
{
	char			**info;
	unsigned int	port;

	if (!cmds[1] || !cmds[1][0])
		return (sv_response(cl, "501 %s", ft_get_error(ERR_WRONG_PARAM)));
	if (!(info = ft_strsplit(cmds[1], ',')))
		return (sv_response(cl, "500 internal error (%s)",
		ft_get_error(ERR_MALLOC)));
	if (ft_tablen(info) != 6 || !sv_validnumber(info, 6))
	{
		ft_tabdel(&info);
		return (sv_response(cl, "501 %s", ft_get_error(ERR_INVALID_PARAM)));
	}
	if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK
	|| cl->errnb[2] != IS_OK || cl->errnb[3] != IS_OK)
		return (sv_response(cl, "421 closing connection"));
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 need to log first"));
	copy_address(cl->data.address, info);
	port = (ft_atoi(info[4]) << 8) + (unsigned char)ft_atoi(info[5]);
	ft_strdel(&cl->data.port);
	ft_tabdel(&info);
	if (!(cl->data.port = ft_itoa(port)))
		return (sv_response(cl, "500 internal error (%s)",
		ft_get_error(ERR_MALLOC)));
	return (sv_response(cl, "200 port changed to %s", cl->data.port));
}

/*
** DATA PORT (PORT) PORT DU CANAL DE DONNEES
**
** PORT <SP> <host-port> <CRLF>
** Example: PORT h1,h2,h3,h4,p1,p2
*/

int				sv_port_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"The argument is a HOST-PORT specification for the data port",
		"to be used in data connection.  There are defaults for both",
		"the user and server data ports, and under normal",
		"circumstances this command and its reply are not needed.  If",
		"this command is used, the argument is the concatenation of a",
		"32-bit internet host address and a 16-bit TCP port address.",
		"This address information is broken into 8-bit fields and the",
		"value of each field is transmitted as a decimal number (in",
		"character string representation).  The fields are separated",
		"by commas.  A port command would be:",
		"",
		"	PORT h1,h2,h3,h4,p1,p2",
		"",
		"where h1 is the high order 8 bits of the internet host",
		"address.", NULL
	};

	return (sv_print_help(cl, cmd, "<host-port>", help));
}
