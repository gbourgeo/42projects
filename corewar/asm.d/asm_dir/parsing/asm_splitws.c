/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:40:56 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/02 00:17:52 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

static int				ft_count_words(const char *s)
{
	int		word;
	int		i;

	i = 0;
	word = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if ((s[i] == ' ' || s[i] == '\t')
				&& s[i + 1] != ' ' && s[i + 1] != '\t')
			word++;
		i++;
	}
	if (s[0] != '\0')
		word++;
	return (word);
}

static char				*ft_mallocd2(const char *s, int *i)
{
	char	*d;
	int		k;

	if (!(d = (char *)malloc(sizeof(d) * (ft_strlen(s)))))
		return (NULL);
	k = 0;
	while (s[*i] != ' ' && s[*i] != '\t' && s[*i])
	{
		d[k] = s[*i];
		k++;
		(*i)++;
	}
	d[k] = '\0';
	while ((s[*i] == '\t' || s[*i] == ' ') && s[*i])
		(*i)++;
	return (d);
}

char					**ft_strsplitws(const char *s)
{
	int		i;
	int		j;
	int		nb_word;
	char	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	nb_word = ft_count_words(s);
	if (!(tab = (char **)malloc(sizeof(s) * (ft_count_words(s) + 2))))
		return (NULL);
	while ((s[i] == '\t' || s[i] == ' ') && s[i])
		i++;
	while (j < nb_word && s[i])
	{
		tab[j] = ft_mallocd2(s, &i);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
