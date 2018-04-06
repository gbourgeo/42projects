/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:34:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/05 16:32:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		ft_modify_env(int i, char *new_p, t_opt *opt)
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
			ft_freestr(&opt->cpy[j]);
			opt->cpy[j] = ret;
			return (1);
		}
		j++;
	}
	return (0);
}

static int		ft_new_env(char *key, char *value, t_opt *opt)
{
	char		**new;
	int			j;

	if ((new = malloc(sizeof(*new) * (ft_tablen(opt->cpy) + 2))) == NULL)
		return (0);
	j = 0;
	while (opt->cpy && opt->cpy[j])
	{
		new[j] = opt->cpy[j];
		j++;
	}
	while (*value == '=')
		value++;
	if ((new[j] = malloc(ft_strlen(key) + ft_strlen(value) + 2)) == NULL)
	{
		free(new);
		return (0);
	}
	ft_strcpy(new[j], key);
	ft_strcat(new[j], "=");
	ft_strcat(new[j], value);
	new[j + 1] = NULL;
	free(opt->cpy);
	opt->cpy = new;
	return (1);
}

int				ft_opt_extra(t_opt *opt)
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
		if (!ft_modify_env(i, tmp + 1, opt) &&
			!ft_new_env(opt->extra[i], tmp + 1, opt))
			return (ft_enverror("malloc failed", 0, opt));
		i++;
	}
	return (0);
}
