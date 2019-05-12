/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:50:35 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 18:11:59 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_H
# define PUT_H

# include "struct.h"

typedef struct	s_cpl_env
{
	int		len;
	int		lenm;
	int		nb_col;
	int		*put;
	int		*nb_ret;
	int		lvl;
	int		is_dol;
	char	bru[257];
	char	*chr;
	char	*ptr;
}				t_cpl_e;

void			get_isput(t_slct *select, int len, int lvl, int *tres);
void			reset_isput(t_slct *select, int len, int lvl);
void			get_psb(t_slct *select, int len, int lvl, int *psb);
int				ret_psb(t_slct *select, int len, int lvl, char *bru);
void			put_select(t_slct *select, int lvl);

void			get_max_len(t_tree *curr, int *lenm);
void			get_put(t_tree *tern, int *ret, char c);
int				get_tstr(t_tree *tern, char *str);
void			get_tree_psb(t_tree *tree, int *psb);

t_slct			*select_branch(t_tree *upper, char *src, int *lenm);

void			reset_put(t_tree *tern);

void			ft_put_tree(t_tree *tern, t_cpl_e env, t_line *line,
		int *car_ret);
void			deal_type(unsigned int type, t_line *line, char *file);

int				put_complet(t_tree *tern, int *put, t_line *line, int *nb_ret);
void			get_complet(t_line *line);
void			set_complet(t_line *line, int set);

int				check_is_file(char *buff, t_line *line);
int				search_to_tmp(char *buff);
void			set_new_glob(t_line *line, t_slst *tmp, int pos);

void			put_branch(t_slct *select, t_cpl_e env, t_line *line,
		int *car_ret);
void			put_select_branch(t_slct *select, t_cpl_e env, t_line *line);
void			put_tree_branch(t_tree *tree, t_cpl_e env, t_line *line);
void			free_select(t_slct *select);
int				get_select(t_line *line, t_tree *tern, t_cpl_e *env, t_slct
		**select);

int				deal_change(t_slct *select, t_tree *tern, t_cpl_e *env);

void			change_buff(t_slct *select, t_cpl_e *env, t_line *line,
		t_tree *tern);

int				have_to_expand(t_line *line);

int				check_put(t_line *line, t_tree *tern, t_slct **select,
		t_cpl_e *env);
void			deal_complet(t_tree *file, t_line *line);

char			*find_separator(char *buff);

/*
**	deaL_completion tools
*/

int				inprint(char *str);
t_tree			*set_tmp(char *buff, int glob);
int				str_chrglob(char *str);
char			*replace_tilde(const char *path, const char *replace);

char			*find_start_pos(char *buff);

/*
**	Tree creation
*/

void			feed_tree(char *str, unsigned char type, t_tree **tern,
		int lvl);

void			fill_tree_bin(char **env, t_tree **ternary);
void			fill_tree_env(char **env, t_tree **ternary);

/*
**	Arrow moving
*/

void			count_elem(t_tree *tree, int *cpt);
void			change_elem(t_tree *tree, int val, int *cpt);

void			deal_slct_key_left(t_tree *select, t_tree *tree, int nb_elem);
void			deal_slct_key_up(t_tree *select, t_tree *tree, int nb_elem,
		int nb_col);
void			deal_slct_key_down(t_tree *select, t_tree *tree, int nb_ele,
		int nb_col);
void			deal_slct_winch(t_tree *select, t_tree *tree);

void			deal_tree_key(t_tree *tree, int nb_col, int key);
void			deal_slct_key(t_slct *select, int nb_col, int key);

/*
**	Deal put tool
*/

int				deal_put(t_line *line, t_cpl_e env, t_slct *select,
		t_tree *tern);
void			deal_all_put(t_line *line, t_tree *tern, t_slct **select,
		t_cpl_e *env);
int				check_put(t_line *line, t_tree *tern, t_slct **select,
		t_cpl_e *env);

#endif
