/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syntax_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 01:20:28 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/21 00:49:46 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

int		syntax_error(t_env *e, int error, char *str, int line)
{
	static char		*tab[] = { NULL, ERR_STR_NAME, ERR_STR_NAME_LEN,
		ERR_STR_NAMENOTF, ERR_STR_COMMENT, ERR_STR_COMMENT_LEN,
		ERR_STR_COMNOTF};

	if (error < 7)
		ft_printf("%s\n", tab[error]);
	else
	{
		if (error == E_LEXICAL)
			ft_dprintf(2, ERR_LEXICAL, str, line);
		else if (error == E_SYNTAX)
			ft_dprintf(2, ERR_SYNTAX, str, line);
		else if (error == E_PARAM)
			ft_dprintf(2, ERR_PARAM, str, line);
		else if (error == E_LAB)
			ft_dprintf(2, ERR_LAB, str, line);
		else if (error == E_OPC)
			ft_dprintf(2, "no instruction availaible on file\n");
		else
			ft_printf("ERROR\n");
	}
	(void)e;
	exit(1);
}
