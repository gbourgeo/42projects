/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter_init.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 22:07:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 20:39:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"
#include "expansion_dollar.h"
#include "expansion_errors.h"

static int		dollar_parameter_end_name(t_exp *param)
{
	return (is_valid_name(param->buff[param->i]));
}

static int		dollar_parameter_end_brace(t_exp *param)
{
	return (is_brace_end(param));
}

static t_end	get_func(int brace, char c)
{
	if (brace)
		return (dollar_parameter_end_brace);
	if (is_special(c))
		return (NULL);
	if (ft_isdigit(c))
		return (NULL);
	if (is_valid_name(c))
		return (dollar_parameter_end_name);
	return (NULL);
}

static int		init_parameter(t_ret *parameter, t_exp *param)
{
	if (param_addchar(param->buff[param->i++], parameter)
	|| ((parameter->brace = param->buff[param->i] == '{')
		&& param_addchar(param->buff[param->i++], parameter))
	|| (parameter->brace && (parameter->hash = param->buff[param->i] == '#')
		&& param_addchar(param->buff[param->i++], parameter)))
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int				expand_dollar_parameter_init(t_ret *parameter, t_exp *param)
{
	t_ret		ret;
	int			(*end_func)(t_exp *);
	int			error;

	error = ERR_NONE;
	ft_memset(&ret, 0, sizeof(ret));
	parameter->head = param->buff + param->i;
	if (init_parameter(parameter, param))
		return (ERR_MALLOC);
	ret.brace = parameter->brace;
	if ((end_func = get_func(parameter->brace, param->buff[param->i])))
	{
		if (parameter->brace && param->buff[param->i] == '$'
		&& !ft_strchr("}:-=?+#%", param->buff[param->i + 1]))
			error = ERR_SYNTAX;
		else if ((error = expand_loop(&ret, param, end_func)) == ERR_NONE)
			error = param_addstr(ret.word, parameter);
	}
	else if (((is_expand_null(parameter) && is_special(param->buff[param->i]))
		|| ft_isdigit(param->buff[param->i]))
	&& param_addchar(param->buff[param->i++], parameter))
		error = ERR_MALLOC;
	expand_free_t_ret(&ret, 0);
	return (error);
}
