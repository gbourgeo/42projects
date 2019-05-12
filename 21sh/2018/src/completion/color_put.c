/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 22:59:17 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 14:42:43 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "libft.h"
#include "shell_lib.h"
#ifdef __linux
# define __USE_MISC
#endif
#include "dirent.h"

static void	deal_access(t_line *line, char *file)
{
	char	*tmp;
	char	*stmp;
	char	*ptr;
	char	*tilde;

	if (!(stmp = sh_strrchr(line->curr->buff, ' ')))
		return ;
	else
		stmp += 1;
	if (!(tilde = sh_strrchr(line->curr->buff, ' ')))
		tilde = line->curr->buff;
	if ((ptr = sh_strrchr(stmp, '/')) && sh_strchr(tilde, '~'))
	{
		tmp = replace_tilde(stmp, getenv("HOME"));
		stmp = ft_strndup(tmp, ft_strrchr(tmp, '/') - tmp + 1);
		free(tmp);
	}
	else if (ptr)
		stmp = ft_strndup(stmp, ptr - stmp + 1);
	else
		stmp = ft_strdup("");
	stmp = ft_strjoinfree(stmp, file, 1);
	if (!access(stmp, X_OK))
		ft_putstr(RED);
	free(stmp);
}

void		deal_type(unsigned int type, t_line *line, char *file)
{
	static char			*col[] = {CYAN, YELLOW, MAGENTA, BLUE, ERROR};
	static unsigned int	ttab[] = {DT_DIR, DT_CHR, DT_LNK, DT_BLK, DT_UNKNOWN};
	int					i;

	i = -1;
	while (++i < (int)(sizeof(col) / sizeof(*col)))
		if (type == ttab[i])
		{
			ft_putstr(col[i]);
			return ;
		}
	if (type == DT_REG)
		deal_access(line, file);
}
