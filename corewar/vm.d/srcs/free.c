/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 00:34:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/03 22:05:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vm.h"

static void		free_proc(t_process *proc)
{
	t_process	*next;

	while (proc)
	{
		next = proc->next;
		if (proc->file && --(*proc->free_file) == 0)
			ft_strdel((char **)&(proc)->file);
		free(proc);
		proc = next;
	}
}

static void		free_bytes(t_bytes *byte)
{
	t_bytes		*next;

	while (byte)
	{
		next = byte->next;
		free(byte);
		byte = next;
	}
}

static void		free_pauses(t_pause *pauses)
{
	t_pause		*next;

	while (pauses)
	{
		next = pauses->next;
		free(pauses);
		pauses = next;
	}
}

void			free_env(t_env *e)
{
	free_proc(e->proc);
	if (e->arena)
		free(e->arena);
	if (e->colors)
		free(e->colors);
	free_bytes(e->bytes);
	free_pauses(e->pauses);
}
