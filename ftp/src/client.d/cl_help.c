/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 09:51:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 06:43:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_help(char **cmds, t_envi *cl)
{
	(void)cmds;
	(void)cl;
	ft_putendl("#*********************************************************#");
	ft_putendl("#*        BIENVENUE SUR LE PROJET FT_P DE GBOURGEO       *#");
	ft_putendl("#*********************************************************#");
	ft_putendl("#*             - Commandes du serveur -                  *#");
	ft_putendl("#* help  : show this help.                               *#");
	ft_putendl("#* ls    : list directory files.                         *#");
	ft_putendl("#* cd    : enter directory.                              *#");
	ft_putendl("#* pwd   : show current directory path.                  *#");
	ft_putendl("#* get   : send file or dir from server to client (you). *#");
	ft_putendl("#* mget  : like 'get' but with multiple arguments.       *#");
	ft_putendl("#* put   : send file or dir from client (you) to server. *#");
	ft_putendl("#* mput  : like 'put' but with multiple arguments.       *#");
	ft_putendl("#* mkdir : create a new directory.                       *#");
	ft_putendl("#* rmdir : remove a directory.                           *#");
	ft_putendl("#* unlink: remove a file.                                *#");
	ft_putendl("#* quit  : exit the program.                             *#");
	ft_putendl("#*                                                       *#");
	ft_putendl("#*             - Commandes du client  -                  *#");
	ft_putendl("#*   Toutes les commandes systemes, precedees par 'l':   *#");
	ft_putendl("#*       lls, lcd, lpwd, lrm, lmkdir, ltouch, ...        *#");
	ft_putendl("#*                                                       *#");
	ft_putendl("#*********************************************************#");
	return (0);
}

int				cl_get_help(t_envi *cl)
{
	file_error("No arguments given.", cl, CLIENT, 0);
	ft_putendl_fd("usage: get [file / dir]", 2);
	ft_putendl_fd("usage: send file / dir from server to client (you)", 2);
	return (1);
}

int				cl_put_help(t_envi *cl)
{
	file_error("No arguments given.", cl, CLIENT, 0);
	ft_putendl_fd("usage: put [file / dir]", 2);
	ft_putendl_fd("usage: send file / dir from client (you) to server", 2);
	return (1);
}
