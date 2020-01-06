/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:16:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/11 21:57:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include "op.h"
# include "vm_ncurse.h"

# if REG_SIZE == 1
#  define REG_CAST uint8_t
# elif REG_SIZE == 2
#  define REG_CAST unsigned short
# elif REG_SIZE == 4
#  define REG_CAST unsigned int
# else
#  define REG_CAST unsigned long
# endif

/*
** Corewar error codes
*/

enum
{
	IS_OK,
	ERR_MISSING_ARG,
	ERR_UNKNOWN_ARG,
	ERR_HELP,
	ERR_DIGIT,
	ERR_WRONG_VALUE,
	ERR_FILENAME,
	ERR_MAX_CHAMP,
	ERR_NUMBER,
	ERR_NO_CHAMP,
	ERR_OPEN,
	ERR_LSEEK,
	ERR_MALLOC,
	ERR_READ,
	ERR_SIZE_LOW,
	ERR_MAGIC,
	ERR_SIZE_DIFF,
	ERR_SIZE_HIGH,
	ERR_NCURSE_MAINWIN,
	ERR_NCURSE_ARENABOX,
	ERR_NCURSE_ARENAWIN,
	ERR_NCURSE_INFOBOX,
	ERR_NCURSE_CHAMPWIN,
	ERR_NCURSE_VMWIN,
	ERR_NCURSE_INFOWIN,
	ERR_NCURSE_WGETCH,
};

typedef struct			s_live
{
	int					last_id;
	char				name[PROG_NAME_LENGTH + 1];
}						t_live;

typedef struct			s_process
{
	int					pos;
	int					pos_y;
	int					id;
	char				*file_name;
	off_t				file_size;
	void				*file;
	size_t				*free_file;
	int					data_size;
	char				reg[REG_NUMBER][REG_SIZE];
	char				pc[REG_SIZE];
	char				carry;
	size_t				instruction_wait;
	uint8_t				instruction;
	size_t				is_alive;
	short				color[2];
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

typedef struct			s_bytes
{
	int					offset;
	int					cycle_to_print;
	short				color;
	struct s_bytes		*next;
	struct s_bytes		*prev;
}						t_bytes;

typedef struct			s_pause
{
	int					cycle_nb;
	struct s_pause		*next;
}						t_pause;

typedef struct			s_env
{
	char				*progname;
	t_pause				*pauses;
	t_ncurse			ncu;
	bool				aff;
	int					dump_cycle;
	int					id;
	int					nb_players;
	t_process			*proc;
	size_t				free_file[MAX_PLAYERS];
	void				*arena;
	short				*colors;
	int					ch;
	int					nb_cycles;
	int					pause;
	int					speed;
	int					cycle_to_die;
	int					last_cycle_to_die;
	int					checks;
	t_bytes				*bytes;
	t_live				live;
	int					live_live[MAX_PLAYERS][2];
}						t_env;

struct s_env			g_env;

typedef struct			s_param
{
	int					type;
	int					value;
	int					size;
}						t_param;

/*
** Signals Handlers
*/
void					corewar_end(int i);
void					ncurses_resizewindow(int sig);

/*
** Errors && Free Functions
*/
void					corewar_errors(int errnb, char *arg, t_env *e);
void					free_env(t_env *e);
t_pause					*remove_pause(t_pause *pauses);

/*
** Get arguments Functions
*/
uint32_t				byteswap_32(uint32_t x);
int						get_arena(t_env *e);
int						get_args(int *ac, char **av, t_env *e);
int						get_colors(t_env *e);
int						get_number(char *av, int *value, int zero);
int						get_pauses(char *av, t_pause **pauses);
int						get_player(t_env *e, char *av);

/*
** Ncurses Functions
*/
int						create_arenabox(t_env *e);
int						create_infobox(t_env *e);
void					ncurses_aff_all(t_env *e);
void					ncurses_end(t_env *e);
int						ncurses_init(t_env *e);
int						ncurses_player_calc_x(int id);
int						ncurses_wgetch(t_env *e);
void					update_aff_arena(int offset, int size, short color[2],
						t_env *e);
void					update_aff_champion_dead(t_env *e, t_process *proc);
void					update_aff_champion_info(t_op *op, t_param *params,
						t_process *proc, t_env *e);
void					update_aff_process_pc(t_env *e);
void					update_aff_vminfo(t_env *e);
void					update_aff_vmstatus(t_env *e);
void					update_aff_processes_live(t_process *proc, t_env *e);

/*
** Game Functions
*/
void					arena_copy(int offset, REG_CAST *value, short color,
						t_env *e);
REG_CAST				arena_get(void *arena, int pc);
REG_CAST				calc_mod(int len, size_t size);
void					dump_map(uint8_t *arena, size_t size);
int						get_params(t_param *params, t_op *op, t_process *proc,
						void *arena);
void					launch_game(t_env *e);
void					move_process_pc(t_process *proc, int len, t_env *e);
t_process				*new_proc(t_process *proc, int value, int flag,
						t_env *e);
int						play_game(t_env *e);
size_t					play_instruction(t_process *proc, t_env *e);
t_process				*remove_proc(t_process **proc, t_env *e);

/*
** Instructions Functions
*/
void					print_live(t_env *e, t_param *params, t_process *proc,
						t_process *tail);
int						op_live(t_param *params, t_process *proc, t_env *e);
int						op_ld(t_param *params, t_process *proc, t_env *e);
int						op_st(t_param *params, t_process *proc, t_env *e);
int						op_add(t_param *params, t_process *proc, t_env *e);
int						op_sub(t_param *params, t_process *proc, t_env *e);
int						op_and(t_param *params, t_process *proc, t_env *e);
int						op_or(t_param *params, t_process *proc, t_env *e);
int						op_xor(t_param *params, t_process *proc, t_env *e);
int						op_zjmp(t_param *params, t_process *proc, t_env *e);
int						op_ldi(t_param *params, t_process *proc, t_env *e);
int						op_sti(t_param *params, t_process *proc, t_env *e);
int						op_fork(t_param *params, t_process *proc, t_env *e);
int						op_lld(t_param *params, t_process *proc, t_env *e);
int						op_lldi(t_param *params, t_process *proc, t_env *e);
int						op_lfork(t_param *params, t_process *proc, t_env *e);
int						op_aff(t_param *params, t_process *proc, t_env *e);

#endif
