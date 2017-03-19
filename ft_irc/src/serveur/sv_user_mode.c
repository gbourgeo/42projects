/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 04:19:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/19 04:19:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			change_user_mode(char c, char mode, t_fd *us, t_fd *cl)
{
	static int		user_nbr[] = { US_MODS1, US_MODS2 };
	char			*tmp;

	tmp = ft_strchr(USER_MODES, mode);
	if (c && (mode == 'O' || mode == 'o'))
		return ;
	if (!c && mode == 'r')
		return ;
	if (c)
		us->reg.umode |= user_nbr[tmp - USER_MODES];
	else
		us->reg.umode &= ~(user_nbr[tmp - USER_MODES]);
	send(cl->fd, ":", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " MODE ", 6, 0);
	send(cl->fd, us->reg.nick, NICK_LEN, 0);
	send(cl->fd, " :", 2, 0);
	send(cl->fd, (c) ? "+" : "-", 1, 0);
	send(cl->fd, &mode, 1, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

void				sv_user_mode(char **cmds, t_fd *us, t_fd *cl)
{
	char			*ptr;
	char			c;

	c = 1;
	if (us->fd != cl->fd)
		return (sv_err(ERR_USERSDONTMATCH, NULL, NULL, cl));
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
			else
				change_user_mode(c, *ptr, us, cl);
			ptr++;
		}
		cmds++;
	}
}
