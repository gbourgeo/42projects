/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_rules.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 23:33:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/10 23:34:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_RULES_H
# define GRAMMAR_RULES_H

# include "token.h"

typedef struct	s_grammar
{
	int			(*rule)(t_param *);
}				t_grammar;

#endif
