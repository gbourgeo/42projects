/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 08:36:31 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include "quote.h"
# include "shell_env.h"
# include "main_tools.h"

/*
** Token Types
*/
enum {
	UNDEFINED = -1,
	TOKEN,
	OPERATOR
};

/*
** Identifiers for token TOKEN
*/
enum {
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	IO_NUMBER,
	RESERVED_WORD,
	COMMENT
};

/*
** Structure for TOKENS
*/
# define NULLTOKEN	(t_token *)0

typedef struct	s_token
{
	const char		*head;
	size_t			len;
	int				type;
	int				id;
	const char		*oldhd;
	size_t			oldlen;
	t_alias			*alias;
	t_quote			*quote;
	const char		*hdocline;
	size_t			hdoclen;
	int				hdocfree;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

/*
** Structure of parameters
** to pass to functions handling characters.
*/

typedef struct	s_param
{
	t_s_env		*e;
	t_token		*head;
	t_token		*token;
	t_hdoc		*hdoc;
	size_t		i;
	char		*line;
}				t_param;

/*
** Structure for quote function handler
*/

typedef struct	s_quote_handler
{
	char		value;
	t_token		*(*handler)(t_param *, int);
	int			type;
}				t_quote_h;

/*
** Structure for OPERATORs, see above
*/
typedef struct	s_ope
{
	char		*name;
	size_t		value;
}				t_ope;

/*
** Token identifiers
*/
# define ID_OPERATOR		{ identify_operator }
# define ID_TOKEN			{ identify_word }

typedef struct	s_call
{
	t_token		*(*identifier)(t_param *);
}				t_call;

/*
** Characters Handler
*/
# define CHAR_QUOTE			{ ft_isquote,    handle_quote }
# define CHAR_COMMENT		{ ft_iscomment,  handle_comment }
# define CHAR_EQUAL			{ ft_isequal,    handle_equal }
# define CHAR_MINUS			{ ft_isminus,    handle_minus }
# define CHAR_NEWLINE		{ ft_isnewline,  handle_newline }
# define CHAR_OPERATOR		{ ft_isoperator, handle_operator }
# define CHAR_WORD			{ ft_isword,     handle_word }

typedef struct	s_func
{
	int			(*is)(int);
	t_token		*(*handler)(t_param *, t_call *);
}				t_func;

/*
** Functions
*/
t_token			*tokenise(char **line, t_s_env *e);
void			token_loop(t_param *param, int (*ft_end)(int));
t_token			*new_token(char *buff, size_t pos);
void			free_token(t_token **token);
void			free_quote(t_quote **quote);
void			free_hdoc(t_hdoc **hdoc);
void			clean_end_token(t_token **token, t_token **head);
t_token			*token_error(int err, t_param *param);

t_token			*handle_alias(t_param *param, t_s_env *e);
t_token			*handle_comment(t_param *param, t_call *token);
t_token			*handle_equal(t_param *param, t_call *token);
t_token			*handle_end_of_input(t_param *param, t_call *token);
t_token			*handle_minus(t_param *param, t_call *token);
t_token			*handle_newline(t_param *param, t_call *token);
t_token			*handle_operator(t_param *param, t_call *token);
t_token			*handle_quote(t_param *param, t_call *token);
t_token			*handle_word(t_param *param, t_call *token);

size_t			check_operator(t_token *token, size_t len);
t_token			*identify_operator(t_param *param);
t_token			*identify_word(t_param *param);

t_token			*quote_line(t_param *param);

int				aliased_line(t_param *param, t_line *line);
int				bslashed_line(t_param *param, t_line *line);
int				dquoted_line(t_param *param, t_line *line);
int				squoted_line(t_param *param, t_line *line);
int				braced_line(t_param *param, t_line *line);
int				dbraced_line(t_param *param, t_line *line);
int				parenthed_line(t_param *param, t_line *line);
int				dparenthed_line(t_param *param, t_line *line);
int				backquoted_line(t_param *param, t_line *line);
int				heredoc_line(t_param *param, t_line *line);

t_token			*backslash(t_param *param, int type);
t_token			*singlequote(t_param *param, int type);
t_token			*doublequote(t_param *param, int type);
t_token			*braceopen(t_param *param, int type);
t_token			*braceclose(t_param *param, int type);
t_token			*parentheseopen(t_param *param, int type);
t_token			*parentheseclose(t_param *param, int type);
t_token			*backquote(t_param *param, int type);

char			*expand_word(t_token *token);

int				ft_iscommand(int c);
int				ft_iscomment(int c);
int				ft_isequal(int c);
int				ft_isname(int c);
int				ft_isminus(int c);
int				ft_isnewline(int c);
int				ft_isnull(int c);
int				ft_isoperator(int c);
int				ft_isquote(int c);
int				ft_isword(int c);

int				is_token_valid_name(t_param *param);
int				is_alias_valid_name(const char *alias, size_t len);

void			debug_tokens(t_token *tokens);

#endif
