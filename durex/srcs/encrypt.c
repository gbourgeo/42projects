/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 22:31:00 by root              #+#    #+#             */
/*   Updated: 2019/08/06 00:43:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* uint64_t uint32_t */
#include <inttypes.h>

#include "durex.h"

static void		encryptString(unsigned char *msg, uint32_t *datablock)
{
	msg[0] = (unsigned char) ((datablock[0] >> 24) & 0xFF);
	msg[1] = (unsigned char) ((datablock[0] >> 16) & 0xFF);
	msg[2] = (unsigned char) ((datablock[0] >> 8) & 0xFF);
	msg[3] = (unsigned char) ((datablock[0]) & 0xFF);
	msg[4] = (unsigned char) ((datablock[1] >> 24) & 0xFF);
	msg[5] = (unsigned char) ((datablock[1] >> 16) & 0xFF);
	msg[6] = (unsigned char) ((datablock[1] >> 8) & 0xFF);
	msg[7] = (unsigned char) ((datablock[1]) & 0xFF);
}

void			encryptFunction(unsigned char *msg, size_t size)
{
	static uint64_t	key[] = { 0x87628687, 0x22548492, 0x12425376, 0x65748391 };
	uint32_t datablock[2];

	if (size % 8) {
		if (size + size % 8 > SERVER_CLIENT_BUFF)
			size -= (size % 8);
		else
			size += (size % 8);
	}
	for (uint32_t j = 0; j < size; j += 8) {
		datablock[0] = (msg[j+0] << 24) | (msg[j+1] << 16)  | (msg[j+2] << 8) | (msg[j+3]);
		datablock[1] = (msg[j+4] << 24) | (msg[j+5] << 16)  | (msg[j+6] << 8) | (msg[j+7]);
		uint32_t v0=datablock[0], v1=datablock[1], sum=0, i; /* initialisation */
		uint32_t delta=0x9e3779b9;                           /* constantes de clef */
		uint32_t k0=key[0], k1=key[1], k2=key[2], k3=key[3]; /* mise en cache de la clef */
		for (i=0; i < 32; i++) {                             /* boucle principale */
			sum += delta;
			v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
			v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
		}
		datablock[0]=v0; datablock[1]=v1;
		encryptString(msg + j, datablock);
	}
}
