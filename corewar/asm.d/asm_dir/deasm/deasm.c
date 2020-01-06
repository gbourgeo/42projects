/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 23:13:32 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/23 02:05:51 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "deasm.h"

static int		create_file(t_info *inf, char *file)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(file);
	if (!(inf->ds_name = (char *)malloc(sizeof(char) * len + 1)))
		return (DS_ERR_MALLOC);
	while (i < len - 3)
	{
		inf->ds_name[i] = file[i];
		i++;
	}
	i -= 2;
	while (i++ < len - 1)
	{
		inf->ds_name[i] = DOT_DS[j];
		j++;
	}
	inf->ds_name[i] = '\0';
	return (0);
}

static int		is_extension(char *file, int i)
{
	int j;

	j = 0;
	while (j < 3)
	{
		if (file[i] != DOT_COR[j])
			return (DS_ERR_EXTENSION);
		j++;
		i++;
	}
	return (0);
}

static int		check_extension(char *file)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(file);
	while (file[i])
	{
		if (file[i] == '.' && i == len - 4)
			return (is_extension(file, i));
		i++;
	}
	return (DS_ERR_EXTENSION);
}

static int		check_file(t_info *inf, char *file)
{
	int ret;

	if ((ret = check_extension(file)) > 0)
		return (ret);
	if ((inf->fd = open(file, O_RDONLY)) == -1)
		return (DS_ERR_OPEN);
	return (create_file(inf, file));
}

int				deasm(t_env *e, char **av, int i)
{
	int		ret;
	int		first;
	t_info	inf;

	ft_memset(&inf, 0, sizeof(inf));
	inf.e = e;
	first = i;
	while (av[i])
	{
		if ((ret = check_file(&inf, av[i])) > 0)
			dsprint_err(ret, av[i]);
		if ((ret = deasm_file(&inf)) > 0)
			return (ret);
		dsflag_print(&inf);
		close(inf.ds_fd);
		close(inf.fd);
		free(inf.ds_name);
		i++;
	}
	ft_printf("%d warrior(s) created.\n", i - first);
	return (0);
}
