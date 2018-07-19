/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 02:17:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/11 00:35:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_base_printf.h"

int			ft_printf(const char *restrict format, ...);
void		ft_printf_write(t_dt *data);

#endif
