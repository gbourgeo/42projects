/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 04:19:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/02 00:43:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			change_user_mode(char c, char mode, t_fd *us, t_fd *cl)
{
	static int		user_nbr[] = { US_MODS1, US_MODS2 };
	char			*tmp;

	tmp = ft_strchr(USER_MODES, mode);
	if ((c && us->reg.umode & user_nbr[tmp - USER_MODES]) ||
		(!c && !(us->reg.umode & user_nbr[tmp - USER_MODES])))
		return ;
	if (c)
		us->reg.umode |= user_nbr[tmp - USER_MODES];
	else
		us->reg.umode &= ~(user_nbr[tmp - USER_MODES]);
	sv_cl_write(":", cl);
	sv_cl_write(cl->reg.nick, cl);
	sv_cl_write("!~", cl);
	sv_cl_write(cl->reg.username, cl);
	sv_cl_write("@", cl);
	sv_cl_write(cl->addr, cl);
	sv_cl_write(" MODE ", cl);
	sv_cl_write(us->reg.nick, cl);
	sv_cl_write(" :", cl);
	sv_cl_write((c) ? "+" : "-", cl);
	sv_cl_write(&mode, cl);
	sv_cl_write(END_CHECK, cl);
}

void				sv_user_mode(char **cmds, t_fd *us, t_fd *cl)
{
	char			*ptr;
	char			c;

	c = 1;
	while (*cmds)
	{
		ptr = *cmds;
		while (*ptr)
		{
			if (*ptr == '+')
				c = 1;
			else if (*ptr == '-')
				c = 0;
			else if (!ft_strchr(USER_MODES, *ptr))
				return (sv_err(ERR_UMODEUNKNOWNFLAG, NULL, NULL, cl));
			else if (*ptr != 'a' &&
					((c && *ptr != 'O' && *ptr != 'o') ||
					(!c && *ptr != 'r')))
				change_user_mode(c, *ptr, us, cl);
			ptr++;
		}
		cmds++;
	}
}
