/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:20:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 08:58:37 by gbourgeo         ###   ########.fr       */
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

# define TEAMNAME_MAX	32

# define LEMIPC_CREATE	IPC_CREAT | IPC_EXCL | SHM_R | SHM_W
# define MY_RAND(nb)	(((nb + 8357) / 3))
# define GET_POS(x, y)	((x) + (y) * MAP_WIDTH)
# define LEMIPC_WINNING_WORDS	"Team \e[31m%d\e[0m won the game !\n"

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
	char			name[TEAMNAME_MAX];
	ULL				uid;
	ULL				total;
}					t_uid;

typedef struct		s_team
{
	key_t			key;
	size_t			size;
	int				shmid;
	int				semid;
	t_uid			*board;
}					t_team;

typedef struct		s_board
{
	ULL				map_width;
	ULL				map_heigth;
	ULL				nb_players;
	ULL				players_ready;
	int				game_in_process;
	ULL				winner;
}					t_board;

typedef struct		s_game
{
	key_t			key;
	size_t			size;
	int				shmid;
	int				semid;
	int				msgqid;
	t_board			*board;
	ULL				*map;
}					t_game;

typedef struct		s_env
{
	const char		*prog;
	t_game			game;
	t_team			teams;
	t_uid			*team;
	t_player		*players;
	ULL				x;
	ULL				y;
	pid_t			pid;
	struct termios	term;
}					t_env;

struct s_env		e;

void				init_game(const char *prog, t_game *game);
void				init_team(const char *prog, t_team *team);
void				init_signal(void (*signal_catcher)(int));

void				ft_create_game(t_game *game);
t_uid				*ft_create_team(const char *name, t_team *team);
void				ft_create_process_to_print_map(void);

void				ft_join_game(t_game *game);
t_uid				*ft_join_team(const char *name, t_team *team);

void				ft_exit(int print_err, char *err);
void				ft_exit_child(int print_err, char *err);

void				ft_termcaps(char **env, struct termios *oldterm);
void				ft_restore_term(struct termios *oldterm);
void				ft_termdo(char *doit);

void				game_signal_catcher(int sig);

void				ft_lock(int semid);
void				ft_unlock(int semid);

void				ft_wait_players(void);
void				ft_launch_game(void);
void				ft_strategy(t_player *players, t_uid *team, t_game *game);

void				ft_sendmsg(ULL uid, t_player *target, t_game *game);
int					ft_rcvmsg(ULL uid, t_player *target, t_game *game);

void				ft_move_to_target(t_player *target, t_game *game);
void				move_horizontaly(int times, t_player *target, ULL *map);
void				move_verticaly(int times, t_player *target, ULL *map);

t_player			*ft_create_players_list(void);

unsigned long long	ft_atoull(const char *str);
char				*ft_getenv(char *str, char **env);

#endif
