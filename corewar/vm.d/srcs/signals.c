/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:17:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/12 22:20:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "vm.h"

void				corewar_end(int sig)
{
	(void)sig;
	ncurses_end(&g_env);
	free_env(&g_env);
	exit(1);
}

void				ncurses_resizewindow(int sig)
{
	if (sig != SIGWINCH)
		return ;
	if ((sig = create_arenabox(&g_env)) == IS_OK)
	{
		if ((sig = create_infobox(&g_env)) == IS_OK)
		{
			ncurses_aff_all(&g_env);
			return ;
		}
	}
	ncurses_end(&g_env);
	free_env(&g_env);
	corewar_errors(sig, NULL, &g_env);
	exit(1);
}
