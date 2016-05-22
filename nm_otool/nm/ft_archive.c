/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_archive.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:21:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 21:15:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int					ft_ar_name(struct ar_hdr *hdr, char **name, size_t *len)
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

static void			ft_aff(void *file, t_base *env, void *start)
{
	t_arc			*tmp;

	env->arc = ft_sort_arc(env->arc);
	ft_check_arc(file, env, start);
	if (env->arc == NULL)
		ft_double_check_arc(file, env, start);
	tmp = env->arc;
	while (tmp)
	{
		if (!env->options[opt_o] && !env->options[opt_A])
		{
			ft_putchar('\n');
			ft_putstr(env->file_name);
			ft_putchar('(');
			ft_putstr(tmp->name);
			ft_putendl("):");
		}
		env->arch_obj_name = tmp->name;
		if (tmp->pos != -1)
			ft_magic(start + tmp->off + sizeof(struct ar_hdr) + tmp->len, env);
		env->arch_obj_name = NULL;
		tmp = tmp->next;
	}
	ft_free_arc(&env->arc);
}

static t_arc		*ft_ar_symb(struct ar_hdr *hdr, int offset, void *start)
{
	void			*data;
	struct ranlib	*ran;
	uint32_t		nran;
	t_arc			*arc;
	t_arc			*tmp;

	data = (char *)(hdr + 1) + offset;
	nran = *(uint32_t *)data / sizeof(*ran);
	ran = (struct ranlib *)(data + sizeof(uint32_t));
	arc = ft_init(nran, NULL);
	tmp = arc;
	while (nran-- && tmp)
	{
		tmp->pos = ran->ran_un.ran_strx;
		tmp->off = ran->ran_off;
		ft_ar_name(start + ran->ran_off, &tmp->name, &tmp->len);
		tmp = tmp->next;
		ran++;
	}
	return (arc);
}

void				ft_archive(void *file, t_base *env)
{
	void			*start;
	struct ar_hdr	*hdr;
	int				is_bsd;
	char			*name;
	size_t			len;

	start = file;
	file += SARMAG;
	env->file_type = FILE_ARCHIVE;
	while (file < env->file + env->file_size)
	{
		hdr = (struct ar_hdr *)file;
		if (ft_strncmp(hdr->ar_fmag, ARFMAG, sizeof(ARFMAG) - 1) == 0)
		{
			is_bsd = ft_ar_name(hdr, &name, &len);
			if (!ft_strncmp(name, SYMDEF, len) ||
				!ft_strncmp(name, SYMDEF_SORTED, len))
				break ;
		}
		file += (ft_atoi(hdr->ar_size) + sizeof(*hdr));
	}
	env->arc = ft_ar_symb(hdr, (is_bsd) ? len : 0, start);
	ft_aff(file + (ft_atoi(hdr->ar_size) + sizeof(*hdr)), env, start);
}
