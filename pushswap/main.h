/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 20:00:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/30 01:03:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MAIN_H
# define	MAIN_H
# include "libft.h"
# include "ps_check_params.h"

typedef struct		s_lib
{
	int				nb;
	struct s_lib	*next;
}					t_lib;

char		*ft_push_swap(t_lib **l_a);
t_lib		*ps_newlist(int c);
void		ps_swap(t_lib **a, char **ret, char *c);
void		ps_swap_list(t_lib **a, t_lib **b, char **ret, char *c);
void		ps_first_to_end(t_lib **a, char **ret, char *c);
void		ps_end_to_first(t_lib **a, char **ret, char *c);
void		ps_goto_end(t_lib **l_c);
int			is_l_a_sorted(t_lib *l_a);

#endif
