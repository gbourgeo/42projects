/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 20:23:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:48:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_TYPES_H
# define EXPANSION_TYPES_H

/*
** Enumeration to retreive the type of each expansions
*/
enum
{
	EXP_BRACE,
	EXP_TILDE,
	EXP_DOLLAR,
	EXP_PARENT,
	EXP_SUBS,
	EXP_NONE,
	EXP_PARAMETER,
	EXP_COMMAND,
	EXP_ARITHMETIC
};

# define OP_EXP_BRACE	{ '{', EXP_BRACE }
# define OP_EXP_TILDE	{ '~', EXP_TILDE }
# define OP_EXP_DOLLAR	{ '$', EXP_DOLLAR }
# define OP_EXP_PARENT	{ '(', EXP_PARENT }
# define OP_EXP_SUBS	{ '`', EXP_SUBS }

typedef struct	s_type
{
	char		c;
	int			value;
}				t_type;

#endif
