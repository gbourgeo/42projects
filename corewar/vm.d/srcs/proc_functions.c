/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:45:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/11 17:49:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

t_process		*new_proc(t_process *proc, int value, int flag, t_env *e)
{
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	ft_memcpy(new, proc, sizeof(*new));
	(*new->free_file)++;
	new->instruction_wait += 1;
	new->instruction = 0;
	if (!flag)
		move_process_pc(new, ((short)value % IDX_MOD), e);
	else
		move_process_pc(new, value, e);
	while (proc->prev && proc->prev->id == proc->id)
		proc = proc->prev;
	new->next = proc;
	if ((new->prev = proc->prev) != NULL)
		new->prev->next = new;
	else
		e->proc = new;
	proc->prev = new;
	update_aff_processes_live(proc, e);
	return (new);
}

t_process		*remove_proc(t_process **proc, t_env *e)
{
	t_process	*p;
	t_process	*next;

	p = *proc;
	if (!p)
		return (NULL);
	next = p->next;
	if (p->prev)
		p->prev->next = p->next;
	else
		e->proc = p->next;
	if (p->next)
		p->next->prev = p->prev;
	if (p->file && --(*p->free_file) == 0)
		ft_strdel((char **)&p->file);
	update_aff_processes_live(p, e);
	ft_bzero(p, sizeof(*p));
	free(*proc);
	*proc = NULL;
	return (next);
}

/*
** system("afplay ~/Desktop/roblox-death-sound-effect.mp3 2>&-");
*/
