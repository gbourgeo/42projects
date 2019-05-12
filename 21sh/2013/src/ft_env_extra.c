/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:34:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 04:02:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		ft_change_var(int i, char *new_p, t_opt *opt)
{
	int			j;
	char		*ret;
	int			len;

	j = 0;
	while (opt->env && opt->env[j])
	{
		if (ft_strcmp(opt->env[j], opt->extra[i]) == '=')
		{
			ret = ft_strchr(opt->env[j], '=');
			while (*new_p == '=')
				new_p++;
			len = ft_strlen(opt->extra[i]) + ft_strlen(new_p) + 1;
			if ((ret = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
				return (0);
			ft_strncpy(ret, opt->extra[i], len);
			ft_strcat(ret, "=");
			ft_strcat(ret, new_p);
			free(opt->env[j]);
			opt->env[j] = ret;
			return (1);
		}
		j++;
	}
	return (0);
}

static int		env_fail(char **n, t_opt *opt)
{
	ft_free(&opt->env);
	opt->env = n;
	return (0);
}

static int		ft_add_env(int i, char *new_p, t_opt *opt)
{
	char		**n;
	int			j;
	int			len;

	n = opt->env;
	if (!(opt->env = ft_tabnew(ft_tablen(n) + 2)))
		return (env_fail(n, opt));
	j = 0;
	while (n && n[j])
	{
		opt->env[j] = n[j];
		j++;
	}
	while (*new_p == '=')
		new_p++;
	len = ft_strlen(opt->extra[i]) + ft_strlen(new_p) + 1;
	if ((opt->env[j] = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (env_fail(n, opt));
	ft_strncpy(opt->env[j], opt->extra[i], len);
	ft_strcat(opt->env[j], "=");
	ft_strcat(opt->env[j], new_p);
	opt->env[j + 1] = NULL;
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
			return (ft_env_error("malloc failed.", 0));
		i++;
	}
	return (0);
}
