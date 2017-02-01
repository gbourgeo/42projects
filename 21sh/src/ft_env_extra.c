/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:34:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/01 23:54:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		ft_change_var(int i, char *new_p, t_opt *opt)
{
	int			j;
	char		*ret;
	int			len;

	j = 0;
	while (opt->cpy && opt->cpy[j])
	{
		if (ft_strcmp(opt->cpy[j], opt->extra[i]) == '=')
		{
			ret = ft_strchr(opt->cpy[j], '=');
			while (*new_p == '=')
				new_p++;
			len = ft_strlen(opt->extra[i]) + ft_strlen(new_p) + 1;
			if ((ret = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
				return (0);
			ft_strncpy(ret, opt->extra[i], len);
			ft_strcat(ret, "=");
			ft_strcat(ret, new_p);
			free(opt->cpy[j]);
			opt->cpy[j] = ret;
			return (1);
		}
		j++;
	}
	return (0);
}

static int		ft_add_env(int i, char *new_p, t_opt *opt)
{
	char		**n;
	int			j;
	int			len;

	n = opt->cpy;
	if ((opt->cpy = (char **)malloc(sizeof(char *) *
									(ft_tablen(n) + 2))) == NULL)
		return (0);
	j = -1;
	while (n && n[++j])
		opt->cpy[j] = n[j];
	while (*new_p == '=')
		new_p++;
	len = ft_strlen(opt->extra[i]) + ft_strlen(new_p) + 1;
	if ((opt->cpy[j] = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
	{
		free(opt->cpy);
		return (0);
	}
	ft_strncpy(opt->cpy[j], opt->extra[i], len);
	ft_strcat(opt->cpy[j], "=");
	ft_strcat(opt->cpy[j], new_p);
	opt->cpy[j + 1] = NULL;
	return (1);
}

int				ft_env_extra(t_opt *opt)
{
	char		*tmp;
	int			i;

	i = 0;
	while (opt->extra[i])
	{
		if (opt->v)
		{
			ft_putstr("#env setenv:\t");
			ft_putendl(opt->extra[i]);
		}
		tmp = ft_strchr(opt->extra[i], '=');
		*tmp = '\0';
		if (!ft_change_var(i, tmp + 1, opt) &&
			!ft_add_env(i, tmp + 1, opt))
			return (ft_env_error("malloc failed", 0, opt));
		i++;
	}
	return (0);
}
