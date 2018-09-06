/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/10 11:40:29 by pc                #+#    #+#             */
/*   Updated: 2018/09/05 09:21:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			ft_get_symb_link(t_file *f, char *path)
{
	ssize_t			r;

	if (!(f->info.s_link = (char*)malloc(sizeof(char) * 256)))
		return ;
	if ((r = readlink(path, f->info.s_link, 256)) == -1)
		ft_perror(path, NULL);
	else
		f->info.s_link[r] = '\0';
}

static void			ft_get_date(t_file *file, t_opt *opt)
{
	char			*date;
	time_t			now;
	static char		en[12][5] = {MONTH_US};
	static char		fr[12][5] = {MONTH_FR};
	int				i;

	i = 0;
	date = ctime(&file->inf.st_atime + opt->date * 2);
	if (date == NULL)
		return (ft_calc_date(file->inf.st_mtime, file, opt));
	while (ft_strncmp(&date[4], en[i], 3))
		i++;
	ft_strncpy(file->info.date, &date[7], 4);
	ft_strncat(file->info.date, fr[i], 5);
	now = time(NULL) - *(&file->inf.st_atime + opt->date * 2);
	if ((now >= 15778463 || now <= -15778463) && !opt->big_t)
		ft_strncat(file->info.date, &date[19], 5);
	else if ((now >= 15778463 || now <= -15778463) && opt->big_t)
		ft_strncat(file->info.date, &date[11], 13);
	else if (!opt->big_t)
		ft_strncat(file->info.date, &date[11], 5);
	else
		ft_strncat(file->info.date, &date[11], 13);
}

void				ft_ls_l(t_file *file, t_dir *dir, char *path, t_opt *opt)
{
	int				len;

	if (!opt->l && !opt->g && !opt->o)
		return ;
	ft_file_type(file->inf.st_mode, file, path);
	if (file->info.permit[10])
		dir->opt[0] = 1;
	file->info.link = (size_t)file->inf.st_nlink;
	len = 1;
	while ((file->inf.st_nlink /= 10) > 0)
		len++;
	dir->opt[1] = len > dir->opt[1] ? len : dir->opt[1];
	ft_owner(dir->opt, file, opt);
	ft_get_date(file, opt);
	dir->d_size += file->inf.st_blocks;
	if (S_ISLNK(file->inf.st_mode))
		ft_get_symb_link(file, path);
}
