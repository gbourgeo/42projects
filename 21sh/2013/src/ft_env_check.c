/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:25:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 04:00:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**ft_env_opt_u(char **cmd, int *i, int j, t_opt *opt)
{
	char		**table;
	int			k;

	if (!(table = (char **)malloc(sizeof(*table) * (ft_tablen(opt->ptr) + 2))))
		return (opt->ptr);
	k = 0;
	while (opt->ptr && opt->ptr[k])
	{
		table[k] = ft_strdup(opt->ptr[k]);
		k++;
	}
	table[k] = (cmd[*i][j] == '\0') ?
		ft_strdup(cmd[++(*i)]) : ft_strdup(&cmd[*i][j]);
	table[k + 1] = NULL;
	if (opt->ptr)
		ft_free(&opt->ptr);
	return (table);
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

static int		ft_p_u_check(char **cmd, int *i, int j, t_opt *opt)
{
	char		**old;
	char		*tmp;

	if (cmd[*i][j] == 'P')
	{
		opt->p = 1;
		tmp = opt->path;
		if ((opt->path = ft_env_opt_p(cmd, i, j + 1, opt)) == tmp)
			return (ft_env_error("malloc failed.", 0));
		return (1);
	}
	else if (cmd[*i][j] == 'u')
	{
		opt->u = 1;
		old = opt->ptr;
		if ((opt->ptr = ft_env_opt_u(cmd, i, j + 1, opt)) == old)
			return (ft_env_error("malloc failed.", 0));
		return (1);
	}
	else
		return (ft_env_error("illegal option", cmd[*i][j]));
	return (0);
}

int				ft_env_check_opt(char **cmd, t_opt *opt, int i, int j)
{
	int			ret;

	while (cmd[i] && cmd[i][0] == '-')
	{
		if (!cmd[i][1])
			opt->i = 1;
		if (!ft_strcmp(cmd[i], "--"))
			return (i);
		j = 0;
		while (cmd[i] && cmd[i][++j])
		{
			if (cmd[i][j] == '-' || cmd[i][j] == 'i')
				opt->i = 1;
			else if (cmd[i][j] == 'v')
				opt->v = 1;
			else if ((ret = ft_p_u_check(cmd, &i, j, opt)) == -1)
				return (-1);
			else if (ret == 1)
				break ;
		}
		if (cmd[i])
			i++;
	}
	return (i);
}

int				ft_env_check_opt_plus(char **cmd, t_opt *opt, int i)
{
	char		**table;
	int			k;

	while (ft_strchr(cmd[i], '='))
	{
		if ((table = ft_tabnew(ft_tablen(opt->extra) + 2)) == NULL)
			return (ft_env_error("malloc failed", 0));
		k = 0;
		while (opt->extra && opt->extra[k])
		{
			table[k] = opt->extra[k];
			k++;
		}
		table[k] = cmd[i];
		table[k + 1] = NULL;
		free(opt->extra);
		opt->extra = table;
		i++;
	}
	return (i);
}
