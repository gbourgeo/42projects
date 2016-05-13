/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_bytes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 15:05:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/12 15:06:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint32_t				ft_swap_bytes(uint32_t num)
{
	return (((num & 0xff000000) >> 24) | ((num & 0x00ff0000) >> 8) |
			((num & 0x0000ff00) << 8) | ((num & 0x000000ff) << 24));
}
