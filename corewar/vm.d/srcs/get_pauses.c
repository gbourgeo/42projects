/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pauses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 02:54:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/13 03:15:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static int	got_pause(int cycle, t_pause *head)
{
	while (head)
	{
		if (head->cycle_nb == cycle)
			return (1);
		head = head->next;
	}
	return (0);
}

static void	sort_pauses(t_pause **pauses)
{
	t_pause	*head;
	t_pause	*tail;
	int		swap;

	head = *pauses;
	while (head)
	{
		tail = head->next;
		while (tail)
		{
			if (tail->cycle_nb < head->cycle_nb)
			{
				swap = tail->cycle_nb;
				tail->cycle_nb = head->cycle_nb;
				head->cycle_nb = swap;
				break ;
			}
			tail = tail->next;
		}
		if (!tail)
			head = head->next;
	}
}

int			get_pauses(char *av, t_pause **pauses)
{
	char	*separator;
	int		err;
	int		value;
	t_pause	*ptr;

	if (!(*pauses = ft_memalloc(sizeof(**pauses))))
		return (ERR_MALLOC);
	ptr = *pauses;
	if ((err = get_number(av, &ptr->cycle_nb, -1)) != IS_OK)
		return (err);
	separator = av;
	while ((separator = ft_strchr(separator, ',')))
	{
		separator++;
		if ((err = get_number(separator, &value, -1)) != IS_OK)
			return (err);
		if (got_pause(value, *pauses))
			continue ;
		if (!(ptr->next = ft_memalloc(sizeof(*ptr->next))))
			return (ERR_MALLOC);
		ptr = ptr->next;
		ptr->cycle_nb = value;
	}
	sort_pauses(pauses);
	return (IS_OK);
}

t_pause		*remove_pause(t_pause *pauses)
{
	t_pause	*next;

	next = NULL;
	if (pauses)
	{
		next = pauses->next;
		free(pauses);
	}
	return (next);
}
