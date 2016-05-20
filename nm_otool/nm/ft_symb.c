/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 04:00:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 07:26:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void			ft_free(t_el *elems)
{
	if (elems)
	{
		if (elems->next)
			ft_free(elems->next);
		ft_memset(elems, '\0', sizeof(*elems));
		free(elems);
		elems = NULL;
	}
}

static t_el			*ft_new_elem(SYM *symb)
{
	t_el			*elem;

	elem = malloc(sizeof(*elem));
	if (elem == NULL)
		ft_putendl_fd("error: ./ft_nm: malloc failed.", 2);
	else
	{
		elem->sym = symb;
		elem->sect = NULL;
		elem->n_type = 0;
		elem->n_sect = 0;
		elem->n_desc = 0;
		elem->n_value = 0;
		elem->type = 0;
		elem->name = NULL;
		elem->indr_name = NULL;
		elem->prev = NULL;
		elem->next = NULL;
	}
	return (elem);
}

static void			ft_fill_elem(size_t i, char *table, t_el *tmp, t_base *env)
{
	if (env->sect.type == IS_32)
	{
		tmp->n_type = env->sect.el[i].n_type;
		tmp->n_sect = env->sect.el[i].n_sect;
		tmp->n_desc = env->sect.el[i].n_desc;
		tmp->n_value = env->sect.el[i].n_value;
		tmp->type = ft_get_type(tmp, env);
		tmp->name = table + env->sect.el[i].n_un.n_strx;
		if ((tmp->n_type & N_STAB) == 0 && (tmp->n_type & N_TYPE) == N_INDR)
			tmp->indr_name = (tmp->n_value == 0) ? "" : table + tmp->n_value;
		return ;
	}
	tmp->n_type = env->sect.elz[i].n_type;
	tmp->n_sect = env->sect.elz[i].n_sect;
	tmp->n_desc = env->sect.elz[i].n_desc;
	tmp->n_value = env->sect.elz[i].n_value;
	tmp->type = ft_get_type(tmp, env);
	tmp->name = table + env->sect.elz[i].n_un.n_strx;
	if ((tmp->n_type & N_STAB) == 0 && (tmp->n_type & N_TYPE) == N_INDR)
		tmp->indr_name = (tmp->n_value == 0) ? "" : table + tmp->n_value;
}

static void			ft_fill_symb(void *file, t_base *env)
{
	size_t			i;
	char			*table;
	t_el			*tmp;

	tmp = env->sect.elems;
	table = file + tmp->sym->stroff;
	if (env->sect.type == IS_32)
		env->sect.el = file + tmp->sym->symoff;
	else
		env->sect.elz = file + tmp->sym->symoff;
	i = 0;
	while (i < tmp->sym->nsyms)
	{
		ft_fill_elem(i, table, tmp, env);
		i++;
		if (i < tmp->sym->nsyms)
		{
			tmp->next = ft_new_elem(tmp->sym);
			if (tmp->next == NULL)
				return (ft_putendl_fd("error: new_elem malloc failed.", 2));
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
	}
}

void				ft_get_symb(void *file, t_base *env)
{
	env->sect.elems = ft_new_elem((SYM *)env->sect.cmd);
	if (env->sect.elems == NULL)
		return (ft_putendl_fd("error: first_elem malloc failed.", 2));
	ft_fill_symb(file, env);
	if (!env->options[opt_a] || env->options[opt_g] || env->options[opt_u] ||
		env->options[opt_U])
		ft_remove(env);
	if (!env->options[opt_p])
		ft_sort_elems(env);
	if (env->file_type != FILE_ARCHIVE && env->nb_files > 1)
	{
		write(1, "\n", 1);
		ft_putstr(env->file_name);
		write(1, ":\n", 2);
	}
	ft_display(env->sect.elems, env);
	if (env->sect.sec)
		free(env->sect.sec);
	ft_free(env->sect.elems);
}
