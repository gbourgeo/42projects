/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_recreate_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 22:39:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 02:01:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static char		*search_back(char *head, char *path)
{
	if (head > path)
		--head;
	while (head > path && *head != '/')
		--head;
	return (head);
}

char			*sv_recreate_path(char *path)
{
	char	*head;
	char	*tail;

	head = path;
	while (*head && *(head + 1))
	{
		if (!(tail = ft_strchr(head + 1, '/')))
			tail = head + ft_strlen(head);
		if (!ft_strncmp(head + 1, ".", tail - head - 1))
			head = ft_strcpy(head, tail);
		else if (!ft_strncmp(head + 1, "..", tail - head - 1))
		{
			if ((head = search_back(head, path)))
				head = ft_strcpy(head, tail);
		}
		else
			head = tail;
	}
	if (!*path)
		ft_strcpy(path, "/");
	return (path);
}
