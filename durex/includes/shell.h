/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 00:46:35 by root              #+#    #+#             */
/*   Updated: 2018/07/20 04:08:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define SHELL_CLIENT_MAX	1
# define SHELL_CLIENT_BUFF	128
# define SHELL_ADDR			"localhost"
# define SHELL_PORT			"4243"

typedef struct	s_sh
{
	int			fd;
	fd_set		fdr;
	fd_set		fdw;
	t_cl		client[SHELL_CLIENT_MAX];
}				t_sh;

#endif
