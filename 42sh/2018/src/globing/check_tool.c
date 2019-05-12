/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 23:32:32 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/07 14:26:19 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"
#include "libft.h"

static int	brack_rev(char **src, char **targ)
{
	int tmp;

	*src += 2;
	while (**src && **src != ']')
	{
		if (**src == **targ)
			return (0);
		else if (*(*src + 1) == '-')
		{
			tmp = **src;
			while (tmp < *(*src + 2))
			{
				if (tmp == *(*src + 2))
					return (0);
				tmp++;
			}
			*src += 2;
		}
		*src += 1;
		tmp = **src;
	}
	*targ += 1;
	*src += 1;
	return (1);
}

static int	brack_norm(char **src, char **targ)
{
	int tmp;

	while (**src && **src != ']' && **src != **targ)
	{
		if (**src == '-')
		{
			while (tmp <= *(*src + 1) && tmp != **targ)
				tmp++;
			if (tmp == **targ)
				*targ += 1;
			if (tmp <= *(*src + 1))
				break ;
		}
		tmp = **src;
		*src += 1;
	}
	**src == **targ ? *targ += 1 : 0;
	if (!**src || **src == ']')
		return (0);
	while (**src && **src != ']')
		*src += 1;
	if (!**src)
		return (0);
	*src += 1;
	return (1);
}

int			deal_bracket(char **src, char **targ)
{
	if (*(*src + 1) == '!')
	{
		if (!brack_rev(src, targ))
			return (0);
	}
	else
	{
		if (!brack_norm(src, targ))
			return (0);
	}
	return (1);
}

static int	deal_dbstar(char **src, char **targ)
{
	int		state;

	if (ft_strchr(*targ, '/'))
		if (check_mln(*src, ft_strchr(*targ, '/') + 1))
			return (1);
	while (**src == '*' || **src == '/')
	{
		state = 0;
		state |= **src == '*' ? IS_STAR : IS_SLASH;
		*src += 1;
	}
	if (state & IS_SLASH && **src == '?')
		return (2);
	while (**targ && **targ != **src)
	{
		if (**src == '?' || **src == '[')
			if (check_mln(*src, *targ + 1))
				return (1);
		*targ += 1;
	}
	if (!**targ && !**src)
		return (1);
	else if ((**targ && !**src) || (!**targ && **src))
		return (0);
	return (2);
}

int			deal_star(char **src, char **targ)
{
	if (*(*src + 1) == '*')
		return (deal_dbstar(src, targ));
	else
	{
		while (**targ && **targ != *(*src + 1) && **targ != '/')
		{
			if (*(*src + 1) == '?' || *(*src + 1) == '[')
				if (check_mln(*src + 1, *targ))
					return (1);
			*targ += 1;
		}
		if (**targ == '/')
			*src += 1;
		if (**targ == *(*src + 1))
		{
			if (**src == '*' && **targ)
				if (check_mln(*src, *targ + 1))
					return (1);
			*src += 1;
		}
	}
	return (2);
}
