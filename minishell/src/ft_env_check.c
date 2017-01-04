/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:25:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/04 16:46:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


static char		**ft_env_opt_u(char **cmd, int *i, int j, t_opt *opt)
{
	char		**tab;
	int			k;

	if ((tab = (char **)malloc(ft_tablen(opt->ptr) + 2)) == NULL)
		return (opt->ptr);
	k = 0;
	while (opt->ptr && opt->ptr[k])
	{
		tab[k] = opt->ptr[k];
		k++;
	}
	tab[k] = (cmd[*i][j] == '\0') ? cmd[++(*i)] : &cmd[*i][j];
	tab[k + 1] = NULL;
	free(opt->ptr);
	return (tab);
}

static char		*ft_env_opt_p(char **cmd, int *i, int j, t_opt *opt)
{
	char		*ret;
	int			len;

	len = ft_strlen(opt->path);
	len += (cmd[*i][j] == 0) ? ft_strlen(cmd[*i + 1]) : ft_strlen(&cmd[*i][j]);
	if ((ret = (char *)malloc(sizeof(*ret) * (len + 2))) == NULL)
		return (opt->path);
	ft_bzero(ret, len + 2);
	ft_strcpy(ret, opt->path);
	if (opt->path)
	{
		free(opt->path);
		ft_strcat(ret, ":");
	}
	if (cmd[*i][j] == '\0')
		ft_strcat(ret, cmd[++(*i)]);
	else
		ft_strcat(ret, &cmd[*i][j]);
	return (ret);
}

int				ft_env_check_opt(char **cmd, t_opt *opt, int i, int j)
{
	while (cmd[++i] && cmd[i][0] == '-')
	{
		if (!cmd[i][1])
			opt->i = 1;
		if (!ft_strcmp(cmd[i], "--"))
			return (i);
		j = 0;
		while (cmd[i][++j])
		{
			if (cmd[i][j] == '-' || cmd[i][j] == 'i')
				opt->i = 1;
			else if (cmd[i][j] == 'v')
				opt->v = 1;
			else if (cmd[i][j] == 'P')
			{
				opt->p = 1;
				if ((opt->path = ft_env_opt_p(cmd, &i, j + 1, opt)) == NULL)
					return (ft_enverror("malloc failed", 0, opt));
				break ;
			}
			else if (cmd[i][j] == 'u')
			{
				opt->u = 1;
				if ((opt->ptr = ft_env_opt_u(cmd, &i, j + 1, opt)) == NULL)
					return (ft_enverror("malloc failed", 0, opt));
				break ;
			}
			else
				return (ft_enverror("illegal option", cmd[i][j], opt));
		}
	}
	return (i);
}

int				ft_env_check_opt_plus(char **cmd, t_opt *opt, int i)
{
	char		**tab;
	int			k;

	while (ft_strchr(cmd[i], '='))
	{
		if ((tab = (char **)malloc(ft_tablen(opt->extra) + 2)) == NULL)
			return (ft_enverror("malloc failed", 0, opt));
		k = 0;
		while (opt->extra && opt->extra[k])
		{
			tab[k] = opt->extra[k];
			k++;
		}
		tab[k] = cmd[i];
		tab[k + 1] = NULL;
		free(opt->extra);
		opt->extra = tab;
		i++;
	}
	return (i);
}
