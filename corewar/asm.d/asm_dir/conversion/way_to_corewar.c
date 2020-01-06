/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_to_corewar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:36:59 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/24 20:09:15 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void		split_way(t_data *data, t_aolist *a)
{
	if (!ft_strcmp(a->tok->lab, NAME_CMD_STRING))
	{
		write_name(data, a->tok->next->lab);
		write_comment(data, a->next->tok->next->lab);
	}
	else
	{
		write_name(data, a->next->tok->next->lab);
		write_comment(data, a->tok->next->lab);
	}
}

int				way_to_corewar(t_data *data, t_aolist *ao)
{
	t_token *tok;

	while (ao && ao->tok == NULL)
		ao = ao->next;
	write_magic(data);
	split_way(data, ao);
	ao = ao->next->next;
	while (ao)
	{
		tok = ao->tok;
		if (tok && tok->type & LABEL)
			tok = tok->next;
		if (tok)
		{
			write_opc(data, tok->val);
			if (data->encoding_byte)
				write_type(data, ao->arg);
			write_param(data, tok->next, ao->arg_size);
		}
		ao = ao->next;
	}
	return (0);
}
