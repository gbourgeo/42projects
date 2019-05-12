/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:24:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/16 22:35:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "shell_lib.h"
#include "command.h"
#include "expansion.h"
#include "expansion_errors.h"

static void		line_quotes(char *quote, char c, char val)
{
	if (!*quote)
		*quote = c;
	else if (*quote == val)
		*quote = 0;
}

static size_t	get_line_length(const char *line)
{
	size_t		i;
	size_t		depth;
	char		quote;

	i = 0;
	depth = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			line_quotes(&quote, line[i], '\'');
		else if (line[i] == '"')
			line_quotes(&quote, line[i], '"');
		else if (line[i] == '\\')
			i++;
		else if (!quote && line[i] == '(')
			++depth;
		else if (!quote && line[i] == ')')
			if (--depth == 0)
				break ;
		i++;
	}
	return (i);
}

static void		expand_subshell_child(int pfd[2], size_t i, t_exp *param)
{
	t_s_env		newe;
	char		*line;

	ft_memcpy(&newe, param->e, sizeof(newe));
	newe.public_env = sh_tabdup((const char **)param->e->public_env);
	newe.private_env = sh_tabdup((const char **)param->e->private_env);
	newe.forked = 1;
	newe.interactive = 0;
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	line = ft_strndup((char *)param->buff + param->i + 2, i - param->i - 2);
	if (line)
		launch_new_cmd(&line, &newe);
	close(STDOUT_FILENO);
	sh_freetab(&newe.public_env);
	sh_freetab(&newe.private_env);
	sh_freestr(&line);
	exit(*newe.ret);
}

void			expand_subshell_father(int pfd[2], pid_t pid, t_ret *ret)
{
	char		buff[1024];
	int			i;

	close(pfd[1]);
	command_wait(pid, 0, NULL);
	while ((i = read(pfd[0], buff, sizeof(buff) - 1)) > 0)
	{
		buff[i] = '\0';
		if (!ret->substitute)
			ret->substitute = ft_strdup(buff);
		else
			ret->substitute = ft_strjoinfree(ret->substitute, buff, 1);
	}
	close(pfd[0]);
	i = 0;
	param_addstr(ret->substitute, ret);
	ret->freeable = 1;
}

int				expand_subshell(t_exp *param, t_ret *ret)
{
	int			pfd[2];
	pid_t		pid;
	size_t		i;

	i = get_line_length(param->buff + param->i + 1) + param->i + 1;
	if (pipe(pfd) < 0)
		return (ERR_PIPE);
	if ((pid = fork()) < 0)
		return (ERR_FORK);
	else if (pid == 0)
		expand_subshell_child(pfd, i, param);
	else
		expand_subshell_father(pfd, pid, ret);
	param->i = i;
	return (ERR_NONE);
}
