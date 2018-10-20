/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:21:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 08:34:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRINTF_H
# define FT_SPRINTF_H

# include "ft_base_printf.h"

int			ft_sprintf(char *str, const char *restrict format, ...);
void		ft_sprintf_write(t_dt *data);

#endif
