/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:51:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/15 17:13:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "vm.h"
#include "libft.h"

static int		get_data(int fd, t_process *proc)
{
	ssize_t		ret;
	size_t		off;
	char		buff[1024];

	off = 0;
	while ((ret = read(fd, buff, sizeof(buff))) > 0)
	{
		ft_memcpy((char *)proc->file + off, buff, ret);
		off += ret;
	}
	if (ret)
		return (ERR_READ);
	if (off <= sizeof(t_header))
		return (ERR_SIZE_LOW);
	if (byteswap_32(((t_header *)proc->file)->magic) != COREWAR_EXEC_MAGIC)
		return (ERR_MAGIC);
	off -= sizeof(t_header);
	if (off != byteswap_32(((t_header *)proc->file)->prog_size))
		return (ERR_SIZE_DIFF);
	if (off > CHAMP_MAX_SIZE)
		return (ERR_SIZE_HIGH);
	proc->data_size = off;
	(*proc->free_file) = 1;
	return (IS_OK);
}

static int		get_player_data(t_process *proc)
{
	int			fd;
	off_t		ret;

	ret = IS_OK;
	if ((fd = open(proc->file_name, O_RDONLY)) < 0)
		ret = ERR_OPEN;
	else if ((proc->file_size = lseek(fd, 0, SEEK_END)) < 0)
		ret = ERR_LSEEK;
	else if (proc->file_size < (off_t)sizeof(t_header))
		ret = ERR_SIZE_LOW;
	else if (proc->file_size > (off_t)sizeof(t_header) + CHAMP_MAX_SIZE)
		ret = ERR_SIZE_HIGH;
	else if ((proc->file = malloc(proc->file_size)) == NULL)
		ret = ERR_MALLOC;
	else if (lseek(fd, 0, SEEK_SET) < 0)
		ret = ERR_LSEEK;
	else
		ret = get_data(fd, proc);
	if (fd >= 0)
		close(fd);
	return (ret);
}

static int		check_id(t_process *proc, int *id)
{
	t_process	*tmp;

	tmp = proc;
	if (*id)
		while (proc)
		{
			if (proc->id == *id)
				return (ERR_NUMBER);
			proc = proc->next;
		}
	else
	{
		*id = 1;
		while (tmp)
		{
			if (tmp->id == *id)
			{
				(*id)++;
				tmp = proc;
			}
			else
				tmp = tmp->next;
		}
	}
	return (IS_OK);
}

int				get_player(t_env *e, char *av)
{
	t_process	*proc;
	t_process	*ptr;

	if (e->nb_players >= MAX_PLAYERS)
		return (ERR_MAX_CHAMP);
	if (check_id(e->proc, &e->id))
		return (ERR_NUMBER);
	if ((proc = ft_memalloc(sizeof(t_process))) == NULL)
		return (ERR_MALLOC);
	proc->pos = e->nb_players;
	proc->id = e->id;
	proc->free_file = &e->free_file[e->nb_players];
	proc->file_name = av;
	ptr = e->proc;
	if (ptr)
		while (ptr->next)
			ptr = ptr->next;
	if (ptr)
		ptr->next = proc;
	else
		e->proc = proc;
	proc->prev = ptr;
	e->id = 0;
	e->nb_players++;
	return (get_player_data(proc));
}
