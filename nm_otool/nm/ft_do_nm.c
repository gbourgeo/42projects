/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 03:24:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/06 12:19:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int					ft_do_nm(t_base *env)
{
	int				ret;
	struct stat		stats;

	ret = 0;
	env->fd = open(env->file_name, O_RDONLY);
	if (env->fd == -1)
		return (ft_nm_error(env, "can't open file: ", 1));
	if (fstat(env->fd, &stats) == -1)
		return (ft_nm_error(env, "can't open file: ", 2));
	env->file_size = stats.st_size;
	env->file = mmap(NULL, stats.st_size, PROT_READ, MAP_PRIVATE, env->fd, 0);
	if (env->file == MAP_FAILED)
		return (ft_nm_error(env, "can't map file: ", 3));
	close(env->fd);
	env->arch_obj_name = NULL;
	ft_magic(env->file, env);
	if (munmap(env->file, stats.st_size) == -1)
		return (ft_nm_error(env, "failed to unmap file: ", -1));
	return (ret);
}
