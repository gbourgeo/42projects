/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/24 17:22:54 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_TYPES_H
# define OPERATOR_TYPES_H

/*
** Identifiers for token OPERATOR
*/

enum
{
	OR_IF_VALUE = 1,
	PIPE_VALUE,
	PIPE_AND_VALUE,
	NOT_VALUE,
	AND_IF_VALUE,
	BACKGRND_VALUE,
	SEMI_VALUE,
	NEWLINE_VALUE,
	DSEMI_VALUE,
	LESS_VALUE = 10,
	LESSAND_VALUE,
	LESS_GREAT_VALUE,
	GREAT_VALUE,
	GREAT_PIPE_VALUE,
	AND_GREAT_VALUE,
	GREAT_AND_VALUE,
	DGREAT_VALUE,
	AND_DGREAT_VALUE,
	DLESS_VALUE
};

# define OR_IF				"||"
# define PIPE				"|"
# define PIPE_AND			"|&"
# define NOT				"!"
# define AND_IF				"&&"
# define BACKGRND			"&"
# define SEMI				";"
# define NEWLINE			"\n"
# define DSEMI				";;"
# define LESS				"<"
# define LESS_AND			"<&"
# define LESS_GREAT			"<>"
# define GREAT				">"
# define GREAT_PIPE			">|"
# define AND_GREAT			"&>"
# define GREAT_AND			">&"
# define DGREAT				">>"
# define AND_DGREAT			"&>>"
# define DLESS				"<<"

# define OP_OR_IF			{ OR_IF,      OR_IF_VALUE }
# define OP_PIPE			{ PIPE,       PIPE_VALUE }
# define OP_PIPE_AND		{ PIPE_AND,   PIPE_AND_VALUE }
# define OP_NOT				{ NOT,        NOT_VALUE }
# define OP_AND_IF			{ AND_IF,     AND_IF_VALUE }
# define OP_BACKGRND		{ BACKGRND,   BACKGRND_VALUE }
# define OP_SEMI			{ SEMI,       SEMI_VALUE }
# define OP_NEWLINE			{ NEWLINE,    NEWLINE_VALUE }
# define OP_DSEMI			{ DSEMI,      DSEMI_VALUE }
# define OP_LESS			{ LESS,       LESS_VALUE }
# define OP_LESSAND			{ LESS_AND,   LESSAND_VALUE }
# define OP_LESS_GREAT		{ LESS_GREAT, LESS_GREAT_VALUE }
# define OP_GREAT			{ GREAT,      GREAT_VALUE }
# define OP_GREAT_PIPE		{ GREAT_PIPE, GREAT_PIPE_VALUE }
# define OP_AND_GREAT		{ AND_GREAT,  AND_GREAT_VALUE }
# define OP_GREAT_AND		{ GREAT_AND,  GREAT_AND_VALUE }
# define OP_DGREAT			{ DGREAT,     DGREAT_VALUE }
# define OP_AND_DGREAT		{ AND_DGREAT, AND_DGREAT_VALUE }
# define OP_DLESS			{ DLESS,      DLESS_VALUE }

#endif
