/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:35:33 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/12 17:56:14 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"

int		has_value(char *var)
{
	int i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		is_local(char *var, char **private_env)
{
	int		len;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	len = var_name_len(var);
	tmp = ft_strsub(var, 0, len);
	while (private_env[i])
	{
		len = var_name_len(private_env[i]);
		tmp2 = ft_strsub(private_env[i], 0, len);
		if (ft_strncmp(tmp2, tmp, len) == 0)
		{
			free(tmp);
			free(tmp2);
			return (1);
		}
		i++;
		free(tmp2);
	}
	free(tmp);
	return (0);
}

int		is_public(char *var, char **public_env)
{
	int		len;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	len = var_name_len(var);
	tmp = ft_strsub(var, 0, len);
	while (public_env[i])
	{
		len = var_name_len(public_env[i]);
		tmp2 = ft_strsub(public_env[i], 0, len);
		if (ft_strncmp(tmp2, tmp, len) == 0)
		{
			free(tmp);
			free(tmp2);
			return (1);
		}
		i++;
		free(tmp2);
	}
	free(tmp);
	return (0);
}

int		is_exported(char *var, char **exported_env)
{
	int		len;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	len = var_name_len(var);
	tmp = ft_strsub(var, 0, len);
	while (exported_env[i])
	{
		len = var_name_len(exported_env[i]);
		tmp2 = ft_strsub(exported_env[i], 0, len);
		if (ft_strncmp(tmp2, tmp, len) == 0)
		{
			free(tmp);
			free(tmp2);
			return (1);
		}
		i++;
		free(tmp2);
	}
	free(tmp);
	return (0);
}

int		var_name_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}
