/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:05:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/15 17:13:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

static void		introduce_champ(t_process *proc)
{
	t_header	*play;
	int			i;

	i = 1;
	ft_printf("Introducing contestants...\n");
	while (proc)
	{
		play = (t_header *)proc->file;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				i++, proc->data_size, play->prog_name, play->comment);
		proc = proc->next;
	}
}

int				main(int ac, char **av)
{
	t_env		*e;
	int			err;

	e = &g_env;
	ft_memset(e, 0, sizeof(*e));
	e->progname = ft_strrchr(av[0], '/');
	e->progname = (e->progname) ? e->progname + 1 : av[0];
	signal(SIGINT, corewar_end);
	if ((err = get_args(&ac, av, e)) == IS_OK)
		if ((err = get_arena(e)) == IS_OK)
			if ((err = ncurses_init(e)) == IS_OK)
				if ((err = get_colors(e)) == IS_OK)
				{
					if (e->ncu.active == FALSE)
						introduce_champ(e->proc);
					launch_game(e);
				}
	ncurses_end(e);
	if (e->dump_cycle == e->nb_cycles)
		dump_map(e->arena, MEM_SIZE);
	free_env(e);
	if (err)
		corewar_errors(err, av[ac], e);
	return (err);
}
