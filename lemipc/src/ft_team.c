/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_team.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 13:46:58 by root              #+#    #+#             */
/*   Updated: 2018/09/08 17:37:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lemipc.h"

static t_uid	*ft_new_team(const char *name, ULL uid)
{
	t_uid		*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->uid = uid;
	new->total = 1;
	new->next = NULL;
	return (new);
}

static t_uid	*ft_add_team_to_teams(const char *name, t_uid **teams)
{
	t_uid		*team;

	team = *teams;
	if (team == NULL)
	{
		*teams = ft_new_team(name, 1);
		return (*teams);
	}
	while (team->next)
		team = team->next;
	team->next = ft_new_team(name, team->uid + 1);
	return (team->next);
}

t_uid			*ft_add_team(const char *name, t_uid **teams)
{
	t_uid		*team;

	team = *teams;
	while (team)
	{
		if (!ft_strcmp(team->name, name))
		{
			team->total++;
			return (team);
		}
		team = team->next;
	}
	return (ft_add_team_to_teams(name, teams));
}
