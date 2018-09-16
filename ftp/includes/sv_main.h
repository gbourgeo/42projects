/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/16 20:54:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include "libft.h"
# include "common.h"
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>

# define COMMANDS "ls", "pwd", "cd", "get", "put", "mkdir", "rmdir", "unlink"
# define CMD_PLUS "quit"
# define FUNCTIONS sv_ls, sv_pwd, sv_cd, sv_get, sv_put, sv_mkdir, sv_rmdir
# define FUNC_PLUS sv_unlink, sv_client_end

enum
{
	v4,
	v6
};

void			sv_loop(t_envi *e);
pid_t			sv_launch_client(int new_fd, t_envi *e);
void			ft_aff_ip(struct addrinfo *p, int v6);
void			sv_fork(int sock, char **args, char *base_path, char **env);
void			sv_prompt(struct sockaddr_in csin, int new_connection);

/*
** commands
*/

int				sv_ls(char **cmds, t_envi *e);
int				sv_pwd(char **cmds, t_envi *e);
int				sv_cd(char **cmds, t_envi *e);
int				sv_get(char **cmds, t_envi *e);
int				sv_send_info(char *file, char *path, int fd, t_envi *e);
int				sv_put(char **cmds, t_envi *e);
int				sv_handle_dir(char *dir, t_envi *e);
int				sv_handle_file(char *file, t_envi *e);
int				sv_mkdir(char **cmds, t_envi *sv);
int				sv_rmdir(char **cmds, t_envi *sv);
int				sv_unlink(char **cmds, t_envi *sv);
int				sv_client_end(char **cmds, t_envi *e);

#endif
