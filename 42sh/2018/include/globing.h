/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 23:28:01 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 16:01:42 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBING_H
# define GLOBING_H

# include "struct.h"

# define IS_SLASH (1 << 0)
# define IS_STAR (1 << 1)
# define IS_REC (1 << 2)
# define IS_MARK (1 << 3)

void					get_new_mln(t_tree *tree, char *str, t_slist **glob,
		t_stint sti);
void					get_glob(t_tree *tree, char *tget, t_slist **glob,
		t_stint sti);
int						glob_brack(t_tree *tree, char *tget, t_slist **glob,
		t_stint sti);
void					glob_star(t_tree *tree, char **tget, t_slist **glob,
		t_stint *sti);
void					glob_slash(t_tree *tree, char **tget, t_slist **glob,
		t_stint *sti);

int						deal_star(char **src, char **targ);
int						deal_bracket(char **src, char **targ);
int						check_mln(char *src, char *targ);
void					ft_nstrstr(char *str, char *to_find, int *nb);
int						ft_nslash(char *str);
void					sort_glob(t_slst *glob);

#endif
