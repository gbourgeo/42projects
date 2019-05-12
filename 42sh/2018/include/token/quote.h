/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:50:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/21 23:03:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

/*
** Enumeration for QUOTES \, ', ", {, $(, (, `
** And here-documents
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
	BACKQUOTE,
	HEREDOCUMENT
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
	size_t			line;
	struct s_quote	*next;
}				t_quote;

/*
** Here Document main structure
*/
# define NULLHDOC	(t_hdoc *)0

typedef struct	s_hdoc
{
	int				type;
	size_t			line;
	struct s_hdoc	*next;
	void			*token;
}				t_hdoc;

t_quote			*quote_add(t_quote **head, int type, size_t line);
void			quote_remove(t_quote **head, int type);
int				quote_type(t_quote *head);
t_quote			*quote_get(t_quote *head);

t_hdoc			*hdoc_add(t_hdoc **head, void *token, size_t line);
void			hdoc_remove(t_hdoc **head);

#endif
