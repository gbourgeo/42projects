/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_special_next.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 23:02:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 19:49:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_special.h"
#include "expansion_errors.h"

int				special_return(t_ret *subs, t_ret *para, t_exp *param)
{
	char	*nbr;
	int		error;

	nbr = ft_itoa(*param->e->ret);
	error = param_addstr(nbr, subs);
	if (nbr)
		free(nbr);
	if (error)
		return (special_error(error, subs->word));
	para->freeable = 1;
	para->substitute = subs->word;
	return (ERR_NONE);
}

int				special_option(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)subs;
	(void)para;
	(void)param;
	return (ERR_NONE);
}

int				special_pid(t_ret *subs, t_ret *para, t_exp *param)
{
	char	*nbr;
	int		error;

	(void)param;
	nbr = ft_itoa(getpid());
	error = param_addstr(nbr, subs);
	if (nbr)
		free(nbr);
	if (error)
		return (special_error(error, subs->word));
	para->freeable = 1;
	para->substitute = subs->word;
	return (ERR_NONE);
}

int				special_jobs(t_ret *subs, t_ret *para, t_exp *param)
{
	(void)subs;
	(void)para;
	(void)param;
	return (ERR_NONE);
}
