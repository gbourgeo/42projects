/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:57:02 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/18 19:46:06 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "shell_term.h"

void	init_new_buff(t_line *line)
{
	free_buff(line);
	if (!(line->curr = ft_memalloc(sizeof(t_buff))))
	{
		line->shell_loop = 0;
		return ;
	}
	if (!(line->curr->buff = ft_memalloc(sizeof(char) * 8192)))
	{
		free(line->curr);
		line->shell_loop = 0;
		return ;
	}
	line->index = 0;
	line->len = 0;
}
