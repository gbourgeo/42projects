/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_away.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 16:16:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/07/31 17:02:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_away_message(char **cmds, t_env *e, t_fd *cl)
{
	int			i;
	int			len;

	i = 1;
	len = 0;
	while (cmds[i] && len < TOPIC_SIZE)
	{
		ft_strncat(cl->away, cmds[i], TOPIC_SIZE - len);
		len += ft_strlen(cmds[i]);
		if (++len < TOPIC_SIZE)
			ft_strcat(cl->away, " ");
		else
			cl->away[len] = '\0';
		i++;
	}
	sv_err(cmds[0], ":You have been marked as being away", cl->fd);
	(void)e;
}

void			sv_away(char **cmds, t_env *e, t_fd *cl)
{
	int			i;
	int			len;

	i = 1;
	len = 0;
	if (!cmds[1] || !*cmds[1])
	{
		cl->flags &= ~FLAGS_AWAY;
		free(cl->away);
		cl->away = NULL;
		sv_err(cmds[0], ":You are no longer marked as being away", cl->fd);
		return ;
	}
	while (cmds[i])
		len += ft_strlen(cmds[i++]);
	len += i;
	if (len > TOPIC_SIZE)
		len = TOPIC_SIZE;
	if (cl->away)
		free(cl->away);
	if ((cl->away = (char *)malloc(sizeof(char) * len)) == NULL)
		return ;
	*cl->away = '\0';
	cl->flags |= FLAGS_AWAY;
	sv_away_message(cmds, e, cl);
}
