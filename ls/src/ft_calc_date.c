/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_date.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/25 07:32:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/06/25 08:04:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** date[5] = { year, month, day, hour, minute };
*/

static void		calc_y_m_d_h_m(time_t *future, int *date)
{
	while (*future >= 31556926)
	{
		date[0]++;
		*future -= 31556926;
	}
	while (*future >= 2629743)
	{
		date[1]++;
		*future -= 2629743;
	}
	while (*future >= 86400)
	{
		date[2]++;
		*future -= 86400;
	}
	while (*future >= 3600)
	{
		date[3]++;
		*future -= 3600;
	}
	while (*future >= 60)
	{
		date[4]++;
		*future -= 60;
	}
}

void			ft_calc_date(time_t future, t_file *file, t_opt *opt)
{
	char		fr[12][5] = {MONTH_FR};
	int			date[5] = {10000, 0, 1, 0, 0};

	future -= 253402300800;
	calc_y_m_d_h_m(&future, &date[0]);
	file->info.date[0] = ' ';
	file->info.date[1] = (date[2] < 10) ? ' ' : '\0';
	ft_strcat(file->info.date, ft_itoa(date[2]));
	file->info.date[3] = ' ';
	ft_strcat(file->info.date, fr[date[1]]);
	if (opt->big_t)
	{
		file->info.date[8] = (date[3] < 10) ? '0' : '\0';
		ft_strcat(file->info.date, ft_itoa(date[3]));
		ft_strcat(file->info.date, ":");
		file->info.date[12] = (date[4] < 10) ? '0' : '\0';
		ft_strcat(file->info.date, ft_itoa(date[4]));
		ft_strcat(file->info.date, ":");
		file->info.date[16] = (future < 10) ? '0' : '\0';
		ft_strcat(file->info.date, ft_itoa(future));
		ft_strcat(file->info.date, " ");
	}
	else
		file->info.date[8] = ' ';
	ft_strcat(file->info.date, ft_itoa(date[0]));
}
