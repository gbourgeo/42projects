/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:21:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 19:50:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "parser.h"
#include "redirection.h"
#include "struct.h"
#include "redirection_errors.h"
#include "main_tools.h"
#include "shell.h"

/*
** Anime must watch (@ touche speciale agrum)
**  - Made in Abyss (TOP 1 gold trop beau, la perfection apres Miyazaki) @
**  - Konosuba (trop drole xD) @
**  - re zero (poignant, mais evite de regarde le dernier ep) @
**  - Erased (deprimant)
**  - Mob psycho 100 (TROP marrant)
**  - One Piece (m'enfin Gillou!!!)
** Les mangas! Et oui Gillou!
**  - Berzerk (gillou il faut) @
**  - Gosu (TOP 1 trop marrant) @
** Pour toi Gillou
**  - Nichijou (wtf)
*/

static int		get_here_doc_line(char **hdoc, char *eof, t_line *line)
{
	while (line->shell_loop && line->tmp[0] == 0)
	{
		put_prompt(line->prompt, *line->ret);
		deal_typing(line);
		if (line->tmp[0] != 4)
			write(STDIN_FILENO, "\n", 1);
		if (line->tmp[0] == -1 || !ft_strcmp(line->curr->buff, eof)
		|| line->tmp[0] == 4)
			break ;
		if (*hdoc == NULL)
			*hdoc = ft_strdup(line->curr->buff);
		else
			*hdoc = ft_strjoinfree(*hdoc, line->curr->buff, 1);
		if (!*hdoc)
			return (ERR_MALLOC);
		if (!(*hdoc = ft_strjoinfree(*hdoc, "\n", 1)))
			return (ERR_MALLOC);
		ft_strclr(line->curr->buff);
		ft_strclr(line->tmp);
		line->beg_buff = line->curr;
		line->index = 0;
		line->len = 0;
	}
	return ((line->tmp[0] == -1) ? ERR_FREE_ALL : ERR_NONE);
}

static int		get_here_doc(t_redirection **redir, t_s_env *e)
{
	t_line		*line;
	char		*promptsave;
	int			error;

	line = get_struct();
	promptsave = line->prompt;
	init_new_buff(line);
	line->prompt = ft_strjoin(HERE_DOC_PROMPT, DEFAULT_PROMPT);
	line->lprompt = ft_strlen(line->prompt);
	line->curr->quoted = 1;
	line->tmp[0] = 0;
	error = get_here_doc_line(&(*redir)->hdoc, (*redir)->arg->cmd[0], line);
	if (line->tmp[0] != -1
	&& ft_strcmp(line->curr->buff, (*redir)->arg->cmd[0]))
		ft_dprintf(STDERR_FILENO, "%s: warning: here-document delimited by "
		"end-of-file (wanted `%s')\n", e->progname, (*redir)->arg->cmd[0]);
	line->shell_loop = 1;
	line->curr->quoted = 0;
	ft_strdel(&line->prompt);
	line->prompt = promptsave;
	line->lprompt = ft_strlen(line->prompt);
	return (error);
}

static int		handle_here_doc(t_redirection **redir, t_s_env *e)
{
	static size_t	fnum = 0;
	int				mode;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	if (!((*redir)->file = ft_strjoinfree("/tmp/.21sh_tmpfile_",
											ft_itoa(fnum++), 2)))
		return (redirect_error(ERR_MALLOC, (*redir)->arg->cmd[0], e));
	if (((*redir)->fdarg = open((*redir)->file, mode, 0600)) < 0)
		return (redirect_open_error((*redir)->file, e));
	if ((*redir)->hdoc)
		write((*redir)->fdarg, (*redir)->hdoc, ft_strlen((*redir)->hdoc));
	return (0);
}

int				redirect_dless(t_redirection **redir, t_s_env *e)
{
	if (e->interactive)
	{
		ft_dprintf(STDERR_FILENO, "%s: warning: here-document delimited by "
		"end-of-file (wanted `%s')\n", e->progname, (*redir)->arg->cmd[0]);
		return (1);
	}
	(*redir)->fdio = (*redir)->ionumber ? ft_atoi((*redir)->ionumber->head) : 0;
	if (get_here_doc(redir, e))
		return (1);
	if (handle_here_doc(redir, e))
		return (1);
	if (((*redir)->fdarg = open((*redir)->file, O_RDONLY)) < 0)
		return (redirect_open_error((*redir)->file, e));
	return (0);
}
