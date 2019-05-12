/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_special_next.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 23:02:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 14:19:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_special.h"
#include "expansion_errors.h"

int				special_return(t_ret *para, t_exp *param)
{
	t_ret	sub;
	char	*nbr;
	int		error;

	ft_memset(&sub, 0, sizeof(sub));
	nbr = ft_itoa(*param->e->ret);
	error = param_addstr(nbr, &sub);
	if (nbr)
		free(nbr);
	if (error)
		return (special_error(error, sub.word));
	para->freeable = 1;
	para->substitute = sub.word;
	return (ERR_NONE);
}

int				special_option(t_ret *para, t_exp *param)
{
	(void)para;
	(void)param;
	return (ERR_NONE);
}

int				special_pid(t_ret *para, t_exp *param)
{
	t_ret	sub;
	char	*nbr;
	int		error;

	(void)param;
	ft_memset(&sub, 0, sizeof(sub));
	nbr = ft_itoa(getpid());
	error = param_addstr(nbr, &sub);
	if (nbr)
		free(nbr);
	if (error)
		return (special_error(error, sub.word));
	para->freeable = 1;
	para->substitute = sub.word;
	return (ERR_NONE);
}

int				special_jobs(t_ret *para, t_exp *param)
{
	if (param->e->bg_val < 2)
		return (ERR_NONE);
	if (!(para->substitute = ft_itoa(param->e->bg_val)))
		return (ERR_MALLOC);
	para->freeable = 1;
	return (ERR_NONE);
}
