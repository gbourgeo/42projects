/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_comparaison.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:46:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/14 19:32:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_tilde.h"

int				tilde_no_param(const char *word)
{
	return (!word || !word[0]);
}

int				tilde_plus(const char *word)
{
	return (word[0] == '+');
}

int				tilde_minus(const char *word)
{
	return (word[0] == '-');
}

int				tilde_digit(const char *word)
{
	char		*ptr;

	ptr = (char *)word;
	if (!ptr)
		return (1);
	while (*ptr)
		if (!ft_isdigit(*ptr++))
			return (0);
	return (1);
}

int				tilde_alpha(const char *word)
{
	char		*ptr;

	ptr = (char *)word;
	if (!ptr)
		return (1);
	while (*ptr)
	{
		if (*ptr != '_' && !ft_isalpha(*ptr))
			return (0);
		ptr++;
	}
	return (1);
}
