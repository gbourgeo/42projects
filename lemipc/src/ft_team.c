/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_team.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 13:46:58 by root              #+#    #+#             */
/*   Updated: 2018/09/12 00:35:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "lemipc.h"

static t_uid		*ft_new_team(size_t size, const char *name, ULL uid)
{
	key_t			key;
	int				shmid;
	t_uid			*new;

	key = ftok(e.prog, 'B');
	if (key == -1)
		return (NULL);
	shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (shmid < 0)
		return (NULL);
	new = shmat(shmid, NULL, 0);
	if (new == (void *)-1)
		return (NULL);
	new->shmid = shmid;
	new->size = size;
	new->name = name;
	new->uid = uid;
	new->total = 1;
	return (new);
}

t_uid				*ft_search_team(const char *name, t_uid **teams, t_ipc *ipc)
{
	t_uid			*team;
	size_t			size;

	team = *teams;
	size = 0;
	while (size < ipc->board->nb_teams * sizeof(*team))
	{
		if (!ft_strcmp((team + size)->name, name))
		{
			(team + size)->total++;
			return (team + size);
		}
		size += sizeof(*team);
	}
	*teams = ft_new_team(size + sizeof(*team), name, ipc->board->nb_teams + 1);
	team = *teams;
	return (teams + ipc->board->nb_teams * sizeof(*team));
}
