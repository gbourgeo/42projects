/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:21:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 07:21:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdio.h>
# include "ft_base_printf.h"

int			ft_fprintf(FILE *stream, const char *restrict format, ...);
void		ft_fprintf_write(t_dt *data);

#endif
