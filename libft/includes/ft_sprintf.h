/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 04:06:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/11 04:06:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRINTF_H
# define FT_SPRINTF_H

# include "ft_base_printf.h"

int			ft_sprintf(char *str, const char *restrict format, ...);
void		ft_sprintf_write(t_dt *data);

#endif
