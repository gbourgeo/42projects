/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_term.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 05:38:23 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/11 17:41:18 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TERM_H
# define SHELL_TERM_H

# include "termios.h"
# include "struct.h"

void			go_home(t_line *line);
void			deal_home(t_line *line);
void			go_end(t_line *line);
void			left_arrow(t_line *line);
void			right_arrow(t_line *line);

void			next_word(t_line *line);
void			prev_word(t_line *line);

int				ft_pchar(int nb);
void			delete_down(void);

void			up_arrow(t_line *line);
void			down_arrow(t_line *line);

void			deal_exit(t_line *line);
void			deal_cancel(t_line *line);
void			ft_clear(t_line *line);

void			del_lines(t_line *line);
void			deal_dleft(t_line *line);
void			del_right(t_line *line);

void			get_typing(t_line *line, int nb_read);
void			term_restore(struct termios *save);
void			define_new_term(struct termios *save);

void			deal_prompt(t_line *line);
void			free_buff(t_line *line);
void			init_new_buff(t_line *line);

void			mv_line_up(t_line *line);
void			mv_line_down(t_line *line);

#endif
