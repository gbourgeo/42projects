/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:46:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/17 04:05:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_MAIN_H
# define CL_MAIN_H

# include <sys/ioctl.h>
# include "libft.h"
# include "common.h"

# define COMMANDS "help", "ls", "pwd", "cd", "get", "put", "lcd", "mkdir"
# define CMD_PLUS "rmdir", "unlink", "mget", "mput"
# define FUNCTIONS cl_help, cl_ls_pwd, cl_ls_pwd, cl_cd, cl_get, cl_put, cl_lcd
# define FUNC_PLUS cl_mkdir, cl_rmdir, cl_unlink, cl_mget_mput, cl_mget_mput

typedef struct	s_client
{
	t_common	*info;
}				t_client;

struct s_client	client;

void			cl_loop(t_client *cl);
void			cl_prompt(t_client *cl);

/*
** commands
*/

int				cl_help(char **cmds, t_client *cl);
int				cl_get_help(t_client *cl);
int				cl_put_help(t_client *cl);
int				cl_ls_pwd(char **cmds, t_client *cl);
int				cl_cd(char **cmds, t_client *cl);
int				cl_get(char **cmds, t_client *cl);
int				cl_put(char **cmds, t_client *cl);
int				cl_lcd(char **args, t_client *cl);
int				cl_mkdir(char **cmds, t_client *cl);
int				cl_rmdir(char **cmds, t_client *cl);
int				cl_unlink(char **cmds, t_client *cl);
int				cl_mget_mput(char **cmds, t_client *cl);
int				cl_end(char *msg, t_client *cl);

int				cl_commands(char **args, t_client *cl);
void			cl_change_pwds(char *pwd, t_client *cl);
char			*cl_getcwd(char *dir, char *lpwd);
int				cl_check_server(int ffd, t_client *cl, char *f);
int				cl_received_dir_files(t_client *cl);
int				cl_get_dir(char *dir, t_client *cl);
int				cl_get_file(char *file, t_client *cl);

#endif
