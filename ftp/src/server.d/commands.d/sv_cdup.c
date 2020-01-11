/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:53:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/11 18:14:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

typedef struct	s_cdup
{
	char	*cmd;
	char	*arg;
	char	*null;
}				t_cdup;

int					sv_cdup(char **cmds, t_client *cl, t_server *sv)
{
	return (sv_cwd((char **)&(t_cdup){ cmds[0], "..", NULL }, cl, sv));
}
