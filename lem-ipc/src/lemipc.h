/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:54:34 by root              #+#    #+#             */
/*   Updated: 2016/12/12 13:14:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include <sys/shm.h>
# include <term.h>

# define WIDTH			10
# define HEIGTH			10
# define MIN_PLAYERS	4

typedef struct		s_data
{
	int				connected;
	int				one;
	int				two;
}					t_data;

typedef struct		s_env
{
	char			*prog;
	struct termios	term;
	int				team;
	key_t			key;
	size_t			size;
	int				shmid;
	t_data			*data;
	char			*map;
	int				semid;
	int				msgqid;
	int				x;
	int				y;
}					t_env;

t_env				e;

void				ft_termcaps(char **env);
void				ft_restore_term(void);
void				ft_termdo(char *doit);
void				ft_exit_server(int print_err, char *err);
void				ft_exit_client(int print_err, char *err);
void				ft_signal(void);
void				ft_create_game(void);
void				ft_join_game(void);
void				ft_lock(void);
void				ft_unlock(void);
void				ft_loop(void);

#endif
