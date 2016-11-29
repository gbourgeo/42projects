/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:54:34 by root              #+#    #+#             */
/*   Updated: 2016/10/28 18:34:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include <sys/shm.h>

# define W_H_MAX		100
# define WIDTH			10
# define HEIGTH			10
# define MAX_PLAYERS	((WIDTH * HEIGTH) / 2) - 1

typedef struct	s_map
{
	int			connected;
	char		*map;
}				t_map;

typedef struct	s_env
{
	char		*prog;
	int			team;
	key_t		key;
	int			size;
	int			shmid;
	t_map		*map;
	int			semid;
	int			msgqid;
}				t_env;

void			ft_err(char *err, t_env *e);
void			ft_err2(char *err, t_env *e);
void			ft_signal(t_env *e);

#endif
