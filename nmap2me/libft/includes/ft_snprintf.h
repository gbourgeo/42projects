/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 08:33:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 08:33:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SNPRINTF_H
# define FT_SNPRINTF_H

# include "ft_base_printf.h"

int			ft_snprintf(char *str, size_t size,
						const char *restrict format, ...);
void		ft_snprintf_write(t_dt *data);

#endif
