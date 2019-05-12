/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserved_words.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:43:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:33:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESERVED_WORDS_H
# define RESERVED_WORDS_H

/*
** Identifiers for token RESERVED_WORD
*/

enum
{
	BANG_VALUE = 1,
	BRACE_OPEN_VALUE,
	BRACE_CLOSE_VALUE,
	CASE_VALUE,
	DO_VALUE,
	DONE_VALUE,
	ELIF_VALUE,
	ELSE_VALUE,
	ESAC_VALUE,
	FI_VALUE = 10,
	FOR_VALUE,
	IF_VALUE,
	IN_VALUE,
	THEN_VALUE,
	UNTIL_VALUE,
	WHILE_VALUE
};

# define BANG			"!"
# define BRACE_OPEN		"{"
# define BRACE_CLOSE	"}"
# define CASE			"case"
# define DO				"do"
# define DONE			"done"
# define ELIF			"elif"
# define ELSE			"else"
# define ESAC			"esac"
# define FI				"fi"
# define FOR			"for"
# define IF				"if"
# define IN				"in"
# define THEN			"then"
# define UNTIL			"until"
# define WHILE			"while"

# define TOKEN_BANG			{ BANG      ,  BANG_VALUE }
# define TOKEN_BRACE_OPEN	{ BRACE_OPEN,  BRACE_OPEN_VALUE }
# define TOKEN_BRACE_CLOSE	{ BRACE_CLOSE, BRACE_CLOSE_VALUE }
# define TOKEN_CASE			{ CASE,        CASE_VALUE }
# define TOKEN_DO			{ DO,          DO_VALUE }
# define TOKEN_DONE			{ DONE,        DONE_VALUE }
# define TOKEN_ELIF			{ ELIF,        ELIF_VALUE }
# define TOKEN_ELSE			{ ELSE,        ELSE_VALUE }
# define TOKEN_ESAC			{ ESAC,        ESAC_VALUE }
# define TOKEN_FI			{ FI,          FI_VALUE }
# define TOKEN_FOR			{ FOR,         FOR_VALUE }
# define TOKEN_IF			{ IF,          IF_VALUE }
# define TOKEN_IN			{ IN,          IN_VALUE }
# define TOKEN_THEN			{ THEN,        THEN_VALUE }
# define TOKEN_UNTIL		{ UNTIL,       UNTIL_VALUE }
# define TOKEN_WHILE		{ WHILE,       WHILE_VALUE }

#endif
