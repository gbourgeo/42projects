/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decrypt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 03:24:33 by root              #+#    #+#             */
/*   Updated: 2018/05/09 15:31:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <sys/types.h>
#include <stdio.h>
	uint64_t data = 0X400430;
	uint32_t k[] = {0x95a8882c, 0x9d2cc113, 0x815aa0cd, 0xa1c489f7};
	uint64_t size = 0X1a0;

static void		compute(uint32_t *v, const uint32_t *k)
{
	uint32_t	sum = 0xC6EF3720;
	uint32_t	delta = 0x9e3779b9;
	uint32_t	v0, v1;
	uint32_t	i;

	v0 = v[0];
	v1 = v[1];
	for (i = 0; i < 32; i++) {
		v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
		v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
		sum -= delta;
	}
	v[0] = v0;
	v[1] = v1;
}

void			decrypt(u_char *data, size_t len, const uint32_t *k)
{
	uint32_t	v[2];
	uint32_t	i;

	len -= (len % 8);
	for (i = 0; i < len; i += 8)
	{
		v[0] = (data[i+0] << 24) | (data[i+1] << 16) | (data[i+2] << 8) | (data[i+3]);
		v[1] = (data[i+4] << 24) | (data[i+5] << 16) | (data[i+6] << 8) | (data[i+7]);
		compute(v, k);
		data[i+0] = (char) ((v[0] >> 24) & 0xFF);
		data[i+1] = (char) ((v[0] >> 16) & 0xFF);
		data[i+2] = (char) ((v[0] >> 8) & 0xFF);
		data[i+3] = (char) ((v[0]) & 0xFF);
		data[i+4] = (char) ((v[1] >> 24) & 0xFF);
		data[i+5] = (char) ((v[1] >> 16) & 0xFF);
		data[i+6] = (char) ((v[1] >> 8) & 0xFF);
		data[i+7] = (char) ((v[1]) & 0xFF);
	}
}

int main()
{

	decrypt((u_char *)&data, size, k);
	return 0;
}
