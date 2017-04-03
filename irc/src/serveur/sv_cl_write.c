/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:43:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/04 00:43:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		check_queue(t_fd *cl)
{
	char		*ptr;

	if (!(ptr = cl->queue) || cl->wr.len == BUFF)
		return ;
	while (*ptr)
	{
		*cl->wr.tail = *ptr;
		cl->wr.tail++;
		if (cl->wr.tail == cl->wr.end)
			cl->wr.tail = cl->wr.start;
		cl->wr.len++;
		if (cl->wr.len == BUFF)
		{
			ptr = ft_strdup(ptr);
			free(cl->queue);
			cl->queue = ptr;
			break ;
		}
		ptr++;
	}
	if (!*ptr)
	{
		free(cl->queue);
		cl->queue = NULL;
	}
}

static void		move_head(ssize_t len, t_fd *cl)
{
	cl->wr.len -= len;
	if (cl->wr.head + len >= cl->wr.end)
	{
		len -= (cl->wr.end - cl->wr.head);
		cl->wr.head = cl->wr.start + len;		
	}
	else
		cl->wr.head += len;
}

void			sv_cl_send(t_fd *cl)
{
	static char	ptr[BUFF + 1] = { 0 };
	ssize_t		ret;

	if (cl->wr.len > 0)
	{
		if (cl->wr.tail <= cl->wr.head)
		{
			ft_strncpy(ptr, cl->wr.head, cl->wr.end - cl->wr.head);
			ft_strncat(ptr, cl->wr.start, cl->wr.tail - cl->wr.start);
			ptr[cl->wr.len] = 0;
		}
		else
			ft_strncpy(ptr, cl->wr.head, cl->wr.tail - cl->wr.head);
		if ((ret = send(cl->fd, ptr, cl->wr.len, 0)) <= 0)
			return ;
		move_head(ret, cl);
		check_queue(cl);
	}
}

void			sv_cl_write(char *str, t_fd *cl)
{
	while (*str)
	{
		if (cl->wr.len == BUFF)
		{
			cl->queue = ft_strjoin(cl->queue, str);
			break ;
		}
		*cl->wr.tail = *str;
		cl->wr.tail++;
		if (cl->wr.tail == cl->wr.end)
			cl->wr.tail = cl->wr.start;
		cl->wr.len++;
		str++;
	}
}
