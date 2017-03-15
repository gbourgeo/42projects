/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_away.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 16:16:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/14 21:13:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/* static void		sv_away_message(char **cmds, t_env *e, t_fd *cl) */
/* { */
/* 	int			i; */
/* 	int			len; */

/* 	i = 1; */
/* 	len = 0; */
/* 	while (cmds[i] && len < TOPIC_SIZE) */
/* 	{ */
/* 		ft_strncat(cl->away, cmds[i], TOPIC_SIZE - len); */
/* 		len += ft_strlen(cmds[i]); */
/* 		if (++len < TOPIC_SIZE) */
/* 			ft_strcat(cl->away, " "); */
/* 		else */
/* 			cl->away[len] = '\0'; */
/* 		i++; */
/* 	} */
/* 	sv_err(cmds[0], ":You have been marked as being away", cl->fd); */
/* 	(void)e; */
/* } */

void			sv_away(char **cmds, t_env *e, t_fd *cl)
{
	(void)cmds;
	(void)e;
	(void)cl;
}
