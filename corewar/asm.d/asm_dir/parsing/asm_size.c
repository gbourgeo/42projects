/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:49:43 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/25 02:03:46 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

size_t		chunk_size(t_token *tok, int id)
{
	size_t		size;

	size = 1;
	if (!tok || !tok->next)
		return (1);
	if (tok->type & LABEL)
		tok = tok->next;
	tok = tok->next;
	if (id >= 0 && g_op_tab[id].encoding_byte)
		size++;
	while (tok)
	{
		if (tok->type & UNDIRECT)
			size += 2;
		else if (id >= 0 && tok->type & DIRECT)
			size += g_op_tab[id].direct_size != 0 ? 2 : 4;
		else
			size += 1;
		tok = tok->next;
	}
	return (size);
}
