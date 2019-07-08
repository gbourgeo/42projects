/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:19:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/08 17:37:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemipc.h"

void		ft_exit_child(int print_err, char *err)
{
	ft_exit_print_winner(print_err, err);
	ft_termdo("ve");
	ft_restore_term(&e.term);
	if (e.game.board != (void *)-1)
	{
		shmdt(e.game.board);
		e.game.board = (void *)-1;
	}
	if (e.teams.board != (void *)-1)
	{
		shmdt(e.teams.board);
		e.teams.board = (void *)-1;
	}
	exit(1);
}
