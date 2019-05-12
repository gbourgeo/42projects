/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:50:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/14 23:20:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

/*
** Enumeration for QUOTES \, ', ", {, $(, (, `.
*/
enum {
	NO_QUOTE = 0,
	BACKSLASH,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	BRACE,
	D_BRACE = 5,
	PARENTHESE,
	D_PARENTHESE,
	BACKQUOTE
};

# define DEFAULT_PROMPT			"> "
# define BACKSLASH_PROMPT		""
# define DQUOTE_PROMPT			"dquote"
# define SQUOTE_PROMPT			"quote"
# define BRACE_PROMPT			"cursh"
# define D_BRACE_PROMPT			"braceparam"
# define PARENTHESE_PROMPT		"subsh"
# define D_PARENTHESE_PROMPT	"cmdsubst"
# define BACKQUOTE_PROMPT		"bquote"
# define HERE_DOC_PROMPT		"heredoc"

/*
** Quote main structure
*/
# define NULLQUOTE	(t_quote *)0

typedef struct	s_quote
{
	int				type;
	int				line;
	struct s_quote	*next;
}				t_quote;

#endif
