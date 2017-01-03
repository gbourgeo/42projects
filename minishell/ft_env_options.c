/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 21:50:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/03 23:36:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**ft_new_env(t_opt *opt, int k)
{
	char		**new;
	int			i;

	if ((new = (char **)malloc(ft_tablen(opt->cpy) - 1)) == NULL)
		return (NULL);
	i = 0;
	while (opt->cpy && opt->cpy[i])
	{
		if (i < k)
			new[i] = opt->cpy[i];
		else if (i > k)
			new[i - 1] = opt->cpy[i];
		i++;
	}
	if (i > 0)
		new[i - 1] = NULL;
	else
		new[i] = NULL;
	return (new);
}

int				ft_opt_u(t_opt *opt)
{
	int			i;
	int			j;

	i = 0;
	if (opt->ptr == NULL || opt->ptr[0] == NULL)
		return (ft_enverror("option requires an argument", 'u', opt));
	while (opt->ptr[i])
	{
		if (opt->v)
		{
			ft_putstr("#env unset:\t");
			ft_putendl(opt->ptr[i]);
		}
		j = 0;
		while (opt->cpy && opt->cpy[j])
		{
			if (ft_strcmp(opt->cpy[j], opt->ptr[i]) == '=' &&
				(opt->cpy = ft_new_env(opt, i)) == NULL)
				return (ft_enverror("malloc failed", 0, opt));
			j++;
		}
		i++;
	}
	return (0);
}

int				ft_opt_i(t_opt *opt)
{
	if (opt->v)
		ft_putendl("#env clearing environ");
	ft_free(&opt->cpy);
	return (0);
}

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
		if (!ft_change_var(i, tmp + 1, opt) &&
			!ft_add_env(i, tmp + 1, opt))
			return (ft_enverror("malloc failed", 0, opt));
		i++;
	}
	return (0);
}
