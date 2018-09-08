/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:20:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/08 17:36:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include <sys/shm.h>

# ifdef __linux__
#  include <termios.h>
# else
#  include <term.h>
# endif
# ifndef ULL
#  define ULL unsigned long long
# endif

# define MAP_WIDTH		10
# define MAP_HEIGTH		10

# define MIN_PPT		2
# define MIN_TEAMS		2
# define MAP_0			0

# define MY_RAND(nb)	((((nb * 7) + 8357) / 3) - 567)
# define GET_POS(x, y)	((x) + (y) * MAP_WIDTH)

/*
** Don't change the order of the members in the s_data structure
*/

typedef struct		s_player
{
	ULL				team;
	ULL				x;
	ULL				y;
	ULL				dist;
	struct s_player	*next;
}					t_player;

typedef struct		s_msg
{
	t_player		ally;
	t_player		ennemy;
}					t_msg;

typedef	struct		s_msgbuf
{
	long			mtype;
	t_msg			msg;
}					t_msgbuf;

typedef struct		s_uid
{
	const char		*name;
	ULL				uid;
	ULL				total;
	struct s_uid	*next;
}					t_uid;

typedef struct		s_board
{
	ULL				players;
	ULL				winner;
	t_uid			*teams;
	int				game_in_process;
}					t_board;

typedef struct		s_ipc
{
	key_t			key;
	size_t			size;
	int				shmid;
	t_board			*board;
	ULL				*map;
	int				semid;
	int				msgqid;
	t_uid			*team;
}					t_ipc;

typedef struct		s_env
{
	const char		*prog;
	t_ipc			player;
	ULL				x;
	ULL				y;
	t_player		*players;
	t_msgbuf		snd;
	t_msgbuf		rcv;
	t_player		*target;
}					t_env;

struct s_env		e;

void				init_ipc(const char *prog, t_ipc *ipc);
unsigned long long	ft_atoull(const char *str);
void				ft_termcaps(char **env, struct termios *oldterm);
void				ft_restore_term(struct termios *oldterm);
void				ft_termdo(char *doit);
void				init_signal(void);
void				ft_exit_creation(int print_err, char *err, t_ipc *ipc);
void				ft_exit_client(int print_err, char *err, t_ipc *ipc);
void				ft_exit(int print_err, char *err);
void				ft_create_game(t_ipc *ipc);
void				ft_join_game(t_ipc *ipc);
void				ft_create_process_to_print_map(t_ipc *ipc);
t_uid				*ft_add_team(const char *name, t_uid **teams);
void				ft_lock(int semid);
void				ft_unlock(int semid);
void				ft_wait_players(void);
void				ft_launch_game(void);
void				ft_strategy(void);
void				ft_sendmsg(t_ipc *ipc);
int					ft_rcvmsg(t_ipc *ipc);
char				*ft_getenv(char *str, char **env);
void				ft_move_to_target(ULL *map);
void				move_horizontaly(int times, ULL *map);
void				move_verticaly(int times, ULL *map);
ULL					ft_nb_players(t_uid *teams);
t_player			*ft_create_players_list(t_ipc *ipc);

#endif
