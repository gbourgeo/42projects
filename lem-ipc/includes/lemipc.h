/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:20:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/07 17:04:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include <sys/shm.h>
# include <term.h>

# define MAP_WIDTH		10
# define MAP_HEIGTH		10
# define MAX_TEAMS		10
# define MAP_VALUE		-1
# define MV				MAP_VALUE

/*
** MAP_VALUE MUST always be different from a team number,
** from 0 to MAX_TEAMS.
*/

typedef struct		s_data
{
	int				end;
	int				connected[MAX_TEAMS];
	int				game_in_process;
}					t_data;

typedef struct		s_player
{
	int				team;
	int				x;
	int				y;
	int				dist;
}					t_player;

typedef	struct		s_msgbuf
{
	long			mtype;
	char			mtext[17];
}					t_msgbuf;

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
	pid_t			pid;
	int				creator;
	int				x;
	int				y;
	t_player		*players;
	t_msgbuf		snd;
	t_msgbuf		rcv;
	t_player		*target;
}					t_env;

struct s_env		e;

void				ft_termcaps(char **env);
void				ft_restore_term(void);
void				ft_termdo(char *doit);
void				ft_signal(void (*f));
void				catch_sig(int sig);
void				ft_exit_server(int print_err, char *err);
void				ft_exit_client(int print_err, char *err);
void				ft_exit(int print_err, char *err);
void				ft_free_exit(void);
void				ft_create_game(void);
void				ft_join_game(void);
void				ft_lock(int semid);
void				ft_unlock(int semid);
void				ft_wait_players(void);
int					ft_check_minimum_players(int *table);
int					ft_check_even_teams(int *table);
void				ft_launch_game(void);
void				ft_strategy(void);
void				ft_sendmsg(void);
int					ft_rcvmsg(void);
char				*ft_getenv(char *str, char **env);
void				ft_move_to_target(void);
int					ft_nb_players(int *players);
void				move_horizontaly(int times);
void				move_verticaly(int times);
void				exec_print(void);

#endif
