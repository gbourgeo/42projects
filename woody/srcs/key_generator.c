/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 11:56:12 by root              #+#    #+#             */
/*   Updated: 2018/05/11 22:29:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <time.h>

void				generate_new_key(uint32_t key[4])
{
	unsigned char	*k;
	size_t			klen;
	size_t			i;

	k = (unsigned char *)key;
	klen = sizeof(*key) * 4;
	i = 0;
	ft_memset(k, 0, klen);
	srand(time(NULL));
	while (i < klen)
	{
		k[i] = rand() % 255;
		i++;
	}
	ft_printf("key_value: %lX%lX%lX%lX\n", key[0], key[1], key[2], key[3]);
}
