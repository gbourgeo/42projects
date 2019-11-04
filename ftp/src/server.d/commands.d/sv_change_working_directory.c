/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_change_working_directory.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 03:23:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/04 19:32:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

int			sv_change_working_directory(char *home, char *pwd)
{
	char	*cwd;
	int		ret;

	if (!(cwd = ft_strjoin(home, pwd)))
		return (ERR_MALLOC);
	ret = chdir(cwd);
	free(cwd);
	return ((ret < 0) ? ERR_CHDIR : IS_OK);
}
