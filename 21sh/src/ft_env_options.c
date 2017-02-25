/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 21:50:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 02:44:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**ft_new_env(t_opt *opt, int k)
{
	char		**new;
	int			i;

	if (!(new = (char **)malloc(sizeof(*new) * ft_tablen(opt->env))))
		return (opt->env);
	i = 0;
	while (opt->env && opt->env[i])
	{
		if (i < k)
			new[i] = ft_strdup(opt->env[i]);
		else if (i > k)
			new[i - 1] = ft_strdup(opt->env[i]);
		i++;
	}
	if (i > 0)
		new[i - 1] = NULL;
	else
		new[i] = NULL;
	ft_free(&opt->env);
	return (new);
}

int				ft_env_u(t_opt *opt)
{
	char		**old;
	int			i;
	int			j;

	i = -1;
	if (opt->ptr == NULL || opt->ptr[0] == '\0')
		return (ft_env_error("option requires an argument", 'u'));
	while (opt->ptr[++i])
	{
		if (opt->v)
			ft_put2endl_fd("#env unset:\t", opt->ptr[i], data.fd);
		old = opt->env;
		j = -1;
		while (opt->env && opt->env[++j])
		{
			if (ft_strcmp(opt->env[j], opt->ptr[i]) == '=')
			{
				if ((opt->env = ft_new_env(opt, j)) == old)
					return (ft_env_error("malloc failed.", 0));
				break ;
			}
		}
	}
	return (0);
}

int				ft_env_i(t_opt *opt)
{
	if (opt->v)
		ft_putendl("#env clearing environ");
	ft_free(&opt->env);
	opt->env = NULL;
	return (0);
}

static char		*ft_search_path(char *cmd, t_opt *opt)
{
	struct stat	buffer;
	char		**paths;
	char		*tmp;
	int			i;

	if ((paths = ft_strsplit(opt->path, ':')) == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = (paths[i][ft_strlen(paths[i]) - 1] != '/') ?
			ft_str2join(paths[i], "/", cmd) : ft_strjoin(paths[i], cmd);
		if (stat(tmp, &buffer) != -1 && access(tmp, F_OK) == 0)
			break ;
		free(tmp);
		tmp = NULL;
		i++;
	}
	ft_free(&paths);
	return (tmp);
}

int				ft_env_p(t_opt *opt, char **cmd)
{
	int			i;

	i = 0;
	if (opt->path == NULL || opt->path[0] == '\0')
		return (ft_env_error("option requires an argument", 'P'));
	if ((opt->cmd = ft_search_path(cmd[0], opt)) == NULL)
		return (ft_env_error("No such file or directory", 0));
	free(cmd[0]);
	cmd[0] = opt->cmd;
	opt->cmd = NULL;
	if (opt->v)
	{
		ft_putstr("#env executing: ");
		ft_putendl(cmd[i]);
		while (cmd[i])
		{
			ft_putstr("#env\targ[");
			ft_putnbr(i);
			ft_putstr("]= '");
			ft_putstr(cmd[i]);
			ft_putendl("'");
			i++;
		}
	}
	return (0);
}
