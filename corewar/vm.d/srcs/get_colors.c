/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:10:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/08 05:23:55 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		fill_colors(short *colors, short color, int size)
{
	int			i;

	i = 0;
	while (i < size)
		colors[i++] = color;
}

int				get_colors(t_env *e)
{
	t_process	*proc;

	proc = e->proc;
	if (e->ncu.active == FALSE)
		return (IS_OK);
	if (!(e->colors = malloc((MEM_SIZE) * sizeof(*e->colors))))
		return (ERR_MALLOC);
	fill_colors(e->colors, 1, MEM_SIZE);
	while (proc)
	{
		fill_colors(e->colors + *(REG_CAST *)proc->pc, proc->color[0],
		proc->data_size);
		proc = proc->next;
	}
	return (IS_OK);
}
