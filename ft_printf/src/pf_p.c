/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 22:33:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/17 12:33:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	get_data(t_dt *data, t_av *av, int *len)
{
	av->ui = va_arg(data->ap, ULL);
	av->s = ft_itoa_base(av->ui, 16);
	av->len = ft_strlen(av->s);
	*len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
}

static void	print_ox(t_dt *data, t_av *av)
{
	int		len;

	len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
	if (!data->flag.minus)
	{
		if (data->flag.min_width <= len + 2 || data->flag.zero)
			write_str(data, "0x", 2);
		while (data->flag.min_width > len + 2 && len++)
			write_char(data, (data->flag.zero) ? '0' : ' ');
		len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
		if (data->flag.min_width >= len + 2 && !data->flag.zero)
			write_str(data, "0x", 2);
	}
	else
		write_str(data, "0x", 2);
}

void		pf_p(t_dt *data)
{
	t_av	av;
	int		len;

	get_data(data, &av, &len);
	print_ox(data, &av);
	if (!av.ui)
		av.len = 0;
	while (data->flag.precision > av.len && data->flag.precision--)
		write_char(data, '0');
	if (!data->flag.point || av.ui)
		write_str(data, av.s, (av.len) ? av.len : 1);
	if (data->flag.minus)
	{
		while (data->flag.min_width > len + 2 && data->flag.min_width--)
			write_char(data, ' ');
	}
	if (av.s)
		free(av.s);
}
