/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_archive.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 14:17:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/22 09:54:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int						ft_ar_name(struct ar_hdr *hdr, char **name, size_t *len)
{
	if (ft_strncmp(hdr->ar_name, AR_EFMT1, sizeof(AR_EFMT1) - 1))
	{
		*name = hdr->ar_name;
		*len = 0;
		while (hdr->ar_name[*len] && *len < sizeof(hdr->ar_name))
			++*len;
		return (0);
	}
	*name = (char *)(hdr + 1);
	*len = ft_atoi(hdr->ar_name + sizeof(AR_EFMT1) - 1);
	return (1);
}

static void				ft_aff_arch(void *file, t_env *env, void *start)
{
	t_arc				*tmp;
	void				*test;

	env->arc = ft_sort_arc(env->arc);
	ft_check_arc(file, env, start);
	if (env->arc == NULL)
		ft_double_check_arc(file, env, start);
	tmp = env->arc;
	while (tmp)
	{
		if (env->options[opt_a])
			ft_print_ar_hdr(tmp->ar_hdr);
		if (OPT_THDL)
		{
			ft_putstr(env->file_name);
			ft_putchar('(');
			ft_putstr(tmp->name);
			ft_putstr("):");
			test = start + tmp->off + sizeof(struct ar_hdr) + tmp->len;
			ft_treat_file(test, env);
		}
		tmp = tmp->next;
	}
	ft_free_arc(&env->arc);
}

static t_arc			*ft_ar_symb(t_env *env, int offset, void *start)
{
	void				*data;
	struct ranlib		*ran;
	uint32_t			nran;
	t_arc				*tmp;

	data = (char *)(env->ar_hdr + 1) + offset;
	nran = *(uint32_t *)data / sizeof(*ran);
	ran = (struct ranlib *)(data + sizeof(uint32_t));
	env->arc = ft_init_arc(nran, NULL);
	tmp = env->arc;
	while (nran-- && tmp)
	{
		tmp->ar_hdr = start + ran->ran_off;
		tmp->pos = ran->ran_un.ran_strx;
		tmp->off = ran->ran_off;
		ft_ar_name(start + ran->ran_off, &tmp->name, &tmp->len);
		tmp = tmp->next;
		ran++;
	}
	return (env->arc);
}

int						ft_archive(void *file, t_env *env)
{
	void				*start;
	int					is_bsd;
	char				*name;
	size_t				len;

	start = file;
	file += SARMAG;
	env->file_type = FILE_ARCH;
	if (env->options[opt_a])
		ft_print_ar_hdr(file);
	while (file < env->file + env->file_size)
	{
		env->ar_hdr = (struct ar_hdr *)file;
		if (!ft_strncmp(env->ar_hdr->ar_fmag, ARFMAG, sizeof(ARFMAG) - 1))
		{
			is_bsd = ft_ar_name(env->ar_hdr, &name, &len);
			if (!ft_strncmp(name, SYMDEF, len) ||
				!ft_strncmp(name, SYMDEF_SORTED, len))
				break ;
		}
		file += (ft_atoi(env->ar_hdr->ar_size) + sizeof(*env->ar_hdr));
	}
	env->arc = ft_ar_symb(env, (is_bsd) ? len : 0, start);
	ft_aff_arch(file, env, start);
	return (0);
}
