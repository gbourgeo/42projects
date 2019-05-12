/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_is_escapable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 12:52:03 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/20 21:02:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"

int		sh_is_escapable(char c)
{
	if (c == '\n')
		return (4);
	if (!ft_isalnum(c) && c != '/' && c != '.' && c != '_' && c != '-'
			&& c != '=')
		return (1);
	return (0);
}
