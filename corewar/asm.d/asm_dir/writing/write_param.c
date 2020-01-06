/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:59:16 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/21 21:06:47 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		reverse_write(t_data *data, unsigned int param, int count)
{
	unsigned char	bin;
	unsigned int	tmp;
	short			rev;

	tmp = param;
	while (count)
	{
		param = tmp;
		bin = param >> count;
		param = (unsigned char)param;
		rev = (param << count) + bin;
		if (count == 8)
			write(data->fd, &rev, 2);
		else
			write(data->fd, &rev, 1);
		count -= 8;
	}
}

void		write_param(t_data *data, t_token *tok, int *tab)
{
	int				i;
	int				len;
	unsigned int	param;

	i = 0;
	while (tok)
	{
		if (tok->type & LAB)
			param = tok->bin;
		else
			param = tok->val;
		if (tab[i] != 1)
		{
			len = tab[i] == 4 ? 24 : 8;
			reverse_write(data, param, len);
		}
		else
			write(data->fd, &param, 1);
		data->pc = data->pc + tab[i];
		tok = tok->next;
		i++;
	}
}
