/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_team.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 13:46:58 by root              #+#    #+#             */
/*   Updated: 2018/09/07 14:02:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

static t_uid	*ft_new_team(const char *name, ULL uid)
{
	t_uid		*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		ft_exit_client(1, "Adding new team");
	new->name = name;
	new->uid = uid;
	new->total = 1;
	new->next = NULL;
	return (new);
}

static t_uid	*ft_add_team(const char *team_name, t_uid **teams)
{
	t_uid		*team;

	team = *teams;
	if (team == NULL)
	{
		*teams = ft_new_team(team_name, 1);
		return (*teams);
	}
	while (team->next)
		team = team->next;
	team->next = ft_new_team(team_name, team->uid + 1);
	return (team->next);
}

t_uid			*ft_add_player(const char *team_name, t_uid **teams)
{
	t_uid		*team;

	team = *teams;
	while (team)
	{
		if (!ft_strcmp(team->name, team_name))
		{
			team->total++;
			return (team);
		}
		team = team->next;
	}
	return (ft_add_team(team_name, teams));
}
