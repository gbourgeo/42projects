/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 04:19:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 21:21:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void				rpl_mode(t_grp *grp, char *limit)
{
	sv_cl_write(":", &grp->from->wr);
	sv_cl_write(grp->from->reg.nick, &grp->from->wr);
	sv_cl_write("!~", &grp->from->wr);
	sv_cl_write(grp->from->reg.username, &grp->from->wr);
	sv_cl_write("@", &grp->from->wr);
	sv_cl_write(grp->from->addr, &grp->from->wr);
	sv_cl_write(" MODE ", &grp->from->wr);
	sv_cl_write(grp->on->name, &grp->from->wr);
	sv_cl_write((grp->c) ? " +" : " -", &grp->from->wr);
	sv_cl_write(grp->ptr, &grp->from->wr);
	if ((*grp->ptr == 'l' || *grp->ptr == 'k') && grp->c)
	{
		sv_cl_write(" ", &grp->from->wr);
		sv_cl_write((*grp->ptr == 'l') ? limit : grp->on->key, &grp->from->wr);
	}
	sv_cl_write(END_CHECK, &grp->from->wr);
	if (limit)
		free(limit);
}

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
	sv_cl_write(":", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write(" MODE ", &cl->wr);
	sv_cl_write(us->reg.nick, &cl->wr);
	sv_cl_write(" :", &cl->wr);
	sv_cl_write((c) ? "+" : "-", &cl->wr);
	sv_cl_write(&mode, &cl->wr);
	sv_cl_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
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
