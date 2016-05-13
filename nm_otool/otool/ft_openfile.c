/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 05:30:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/12 20:59:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int			ft_file_error(char *errmess, t_env *env, int errnum)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(env->prog_name, 2);
	ft_putstr_fd(errmess, 2);
	ft_putstr_fd(env->file_name, 2);
	if (errnum == 1)
		ft_putstr_fd(" (No such file or directory)", 2);
	if (errnum == 2)
		ft_putstr_fd(" (Permission denied)", 2);
	if (errnum == 3)
		ft_putstr_fd(" (Invalid argument)", 2);
	ft_putchar_fd('\n', 2);
	if (env->fd >= 0)
		close(env->fd);
	return (1);
}

int					ft_openfile(t_env *env)
{
	struct stat		stats;

	env->fd = open(env->file_name, O_RDONLY);
	if (env->fd == -1)
		return (ft_file_error(": can't open file: ", env, 1));
	if (fstat(env->fd, &stats) == -1)
		return (ft_file_error(": can't stat file: ", env, 2));
	env->file_size = stats.st_size;
	env->file = mmap(NULL, stats.st_size, PROT_READ, MAP_PRIVATE, env->fd, 0);
	if (env->file == MAP_FAILED)
		return (ft_file_error(": can't map file: ", env, 3));
	close(env->fd);
	ft_treat_file(env->file, env);
	if (munmap(env->file, stats.st_size) == -1)
		return (ft_file_error(": can't munmap file: ", env, -1));
	return (0);
}
