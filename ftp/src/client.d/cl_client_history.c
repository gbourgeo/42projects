/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:50:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/20 17:58:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include "cl_main.h"

int				cl_history_init(t_client *cl)
{
	char		*line;
	int			count;
	int			fd;

	line = NULL;
	count = 0;
	fd = open(CL_HIST_FILE, O_CREAT | O_RDONLY, 0644);
	if (fd < 0)
		return (ERR_OPEN);
	while (get_next_line(fd, &line) > 0 && count < CL_HIST_SIZE)
	{
		if (line && *line)
		{
			cl->hist = cl_history_new(line, cl->hist);
			count++;
		}
	}
	cl->hist = cl_history_new(NULL, cl->hist);
	return (IS_OK);
}

t_hist			*cl_history_new(char *line, t_hist *hist)
{
	t_hist		*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (hist);
	new->line = line;
	new->next = hist;
	if (hist)
		hist->prev = new;
	return (new);
}

t_hist			*cl_history_add(char *line, t_hist *hist)
{
	t_hist		*ptr;
	t_hist		*next;
	int			count;

	count = 1;
	if (hist)
	{
		while (hist->prev)
			hist = hist->prev;
		ft_strdel(&hist->line);
		hist->line = ft_strdup(line);
		ptr = hist;
		while (ptr)
		{
			if (count++ > CL_HIST_SIZE)
			{
				ft_strdel(&ptr->next->line);
				next = ptr->next->next;
				free(ptr->next);
				ptr->next = next;
			}
			else
				ptr = ptr->next;
		}
	}
	return (cl_history_new(NULL, hist));
}
