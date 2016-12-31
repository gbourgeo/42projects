/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 17:16:47 by gilles            #+#    #+#             */
/*   Updated: 2015/06/25 02:55:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int			ft_handle_file(struct stat *buf, char *file_name, t_opt *opt)
{
	t_file			*tmp;

	tmp = malloc(sizeof(*tmp));
	if (tmp == NULL)
		return (1);
	ft_clear_file(tmp);
	tmp->name = ft_strdup(file_name);
	tmp->inf = *buf;
	if (opt->l || opt->g || opt->o)
		ft_ls_l(tmp, &opt->files, file_name, opt);
	tmp->next = opt->files.file;
	if (tmp->next)
		tmp->next->prev = tmp;
	opt->files.file = tmp;
	return (0);
}

static int			ft_handle_dir(struct stat *buf, char *dir_name, t_opt *opt)
{
	opt->dir = ft_create_dir(buf, dir_name, opt);
	if (!opt->r && opt->big_r && opt->dir && opt->dir->file)
		ft_ls_big_r(opt->dir, opt);
	if (opt->dir)
		return (0);
	return (1);
}

static int			ft_handle_link(struct stat *buf, char *name, t_opt *opt)
{
	t_dir		*tmp;

	if (!opt->l && !opt->g && !opt->o)
	{
		if (stat(name, buf))
			return (ft_handle_file(buf, name, opt));
		if (S_ISDIR(buf->st_mode))
		{
			opt->ret = ft_handle_dir(buf, name, opt);
			if (opt->dir && opt->dir->error != -1)
			{
				tmp = opt->dir->next;
				tmp->prev = opt->dir->prev;
				free(opt->dir->name);
				free(opt->dir);
				opt->dir = tmp;
			}
			else
				return (0);
		}
	}
	return (ft_handle_file(buf, name, opt));
}

int					ft_get_dir(char *dir_name, t_opt *opt)
{
	struct stat		buf;

	if (lstat(dir_name, &buf))
		return (ft_perror(dir_name, NULL));
	if (S_ISLNK(buf.st_mode))
		return (ft_handle_link(&buf, dir_name, opt));
	if (S_ISDIR(buf.st_mode) && !opt->d)
		return (ft_handle_dir(&buf, dir_name, opt));
	return (ft_handle_file(&buf, dir_name, opt));
}
