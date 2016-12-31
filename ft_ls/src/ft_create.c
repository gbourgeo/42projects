/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/05 22:22:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/31 22:23:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			ft_get_inside_dir(char *name, t_dir *dir, t_opt *options)
{
	char			*path;

	if (ft_strcmp(name, ".") && ft_strcmp(name, "..") &&
		(*name != '.' || options->a || options->f))
	{
		if (dir->name[ft_strlen(dir->name) - 1] == '/')
			path = ft_strjoin(dir->name, name);
		else
		{
			path = ft_strnew(ft_strlen(dir->name) + ft_strlen(name) + 2);
			path = ft_strcpy(path, dir->name);
			path = ft_strcat(path, "/");
			path = ft_strcat(path, name);
		}
		options->ret = ft_get_dir(path, options);
		free(path);
		options->nb_dir++;
	}
}

static int			ft_get_stats(t_file *tmp, t_dir *dir, t_opt *opt)
{
	char		*path;

	if (dir->name[ft_strlen(dir->name) - 1] == '/')
		path = ft_strjoin(dir->name, tmp->name);
	else
	{
		path = ft_strnew(ft_strlen(dir->name) + ft_strlen(tmp->name) + 2);
		path = ft_strcpy(path, dir->name);
		path = ft_strcat(path, "/");
		path = ft_strcat(path, tmp->name);
	}
	if (path == NULL)
		return (-1);
	if (lstat(path, &tmp->inf) == 0)
		ft_ls_l(tmp, dir, path, opt);
	else
		opt->ret = ft_perror(path, NULL);
	if (path)
		free(path);
	return (opt->ret);
}

static t_file		*ft_get_files(DIR *rep, t_dir *dir, t_opt *op, t_file *tmp)
{
	struct dirent	*file;

	while ((file = readdir(rep)))
	{
		if (op->a || op->f || ((*file->d_name != '.' || op->big_a) &&
			ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, "..")))
		{
			if ((tmp = malloc(sizeof(*tmp))) == NULL)
				continue ;
			ft_clear_file(tmp);
			tmp->name = ft_strdup(file->d_name);
			tmp->type = file->d_type;
			if (tmp->type == DT_DIR && op->big_r && op->r)
				ft_get_inside_dir(tmp->name, dir, op);
			if (op->l || op->t || op->g || op->o || op->big_s || op->big_f)
				ft_get_stats(tmp, dir, op);
			if ((tmp->next = dir->file) && tmp->next)
				tmp->next->prev = tmp;
			dir->f_nbr++;
			if (ft_strlen(tmp->name) > dir->f_maxlen)
				dir->f_maxlen = ft_strlen(tmp->name);
			dir->file = tmp;
		}
	}
	return (tmp);
}

t_dir				*ft_create_dir(struct stat *buf, char *dir_name, t_opt *opt)
{
	t_dir			*dir;
	DIR				*rep;
	int				errno;

	if ((dir = malloc(sizeof(*dir))) == NULL)
		return (opt->dir);
	ft_clear_dir(dir);
	dir->name = ft_strdup(dir_name);
	dir->inf = *buf;
	if ((rep = opendir(dir_name)) != NULL)
	{
		dir->file = ft_get_files(rep, dir, opt, NULL);
		closedir(rep);
		if (dir->file && !opt->f)
			ft_sort_by_name(&dir->file);
	}
	else
		dir->error = errno;
	dir->next = opt->dir;
	if (dir->next)
		dir->next->prev = dir;
	return (dir);
}
