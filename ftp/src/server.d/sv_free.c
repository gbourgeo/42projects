/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:27:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/25 23:41:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sv_main.h"

void			sv_free_user(t_user **user)
{
	t_user		*next;

	if (user)
		while (*user)
		{
			ft_strdel(&(*user)->name);
			ft_strdel(&(*user)->pass);
			next = (*user)->next;
			ft_bzero(*user, sizeof(**user));
			free(*user);
			*user = next;
		}
}

void			sv_free_env(t_env *env)
{
	if (env->path)
		free(env->path);
	if (env->home)
		free(env->home);
}
