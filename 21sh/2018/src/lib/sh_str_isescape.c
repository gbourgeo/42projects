/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_str_isescape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:48:17 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 14:05:46 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"

int		sh_str_isescape(const char *str)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
		count += sh_is_escapable(str[i]);
	return (count);
}
