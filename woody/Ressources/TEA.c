/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 22:21:02 by root              #+#    #+#             */
/*   Updated: 2018/07/12 07:47:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <stdio.h>

void chiffrer (unsigned char* data, uint32_t size, uint32_t* k) {
	size -= (size % 8);
	for (uint32_t j = 0; j < size; j += 8) {
		uint32_t datablock[2];

		datablock[0] = (data[j+0] << 24) | (data[j+1] << 16)  | (data[j+2] << 8) | (data[j+3]);
		datablock[1] = (data[j+4] << 24) | (data[j+5] << 16)  | (data[j+6] << 8) | (data[j+7]);

		uint32_t v0=datablock[0], v1=datablock[1], sum=0, i;           /* initialisation */
		uint32_t delta=0x9e3779b9;                     /* constantes de clef */
		uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* mise en cache de la clef */
		for (i=0; i < 32; i++) {                       /* boucle principale */
			sum += delta;
			v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
			v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
		}
		datablock[0]=v0; datablock[1]=v1;
		
		data[j+0] = (char) ((datablock[0] >> 24) & 0xFF);
		data[j+1] = (char) ((datablock[0] >> 16) & 0xFF);
		data[j+2] = (char) ((datablock[0] >> 8) & 0xFF);
		data[j+3] = (char) ((datablock[0]) & 0xFF);
		data[j+4] = (char) ((datablock[1] >> 24) & 0xFF);
		data[j+5] = (char) ((datablock[1] >> 16) & 0xFF);
		data[j+6] = (char) ((datablock[1] >> 8) & 0xFF);
		data[j+7] = (char) ((datablock[1]) & 0xFF);
	}
}

void dechiffrer (unsigned char* data, uint32_t size, uint32_t* k) {
	size -= (size % 8);
	for (uint32_t j = 0; j < size; j += 8) {
		uint32_t datablock[2];

		datablock[0] = (data[j+0] << 24) | (data[j+1] << 16)  | (data[j+2] << 8) | (data[j+3]);
		datablock[1] = (data[j+4] << 24) | (data[j+5] << 16)  | (data[j+6] << 8) | (data[j+7]);

		uint32_t v0=datablock[0], v1=datablock[1], sum=0xC6EF3720, i;  /* initialisation */
		uint32_t delta=0x9e3779b9;                     /* constantes de clefs */
		uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* mise en cache de la clef */
		for (i=0; i<32; i++) {                         /* boucle principale */
			v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
			v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
			sum -= delta;
		}
		datablock[0]=v0; datablock[1]=v1;
		
		data[j+0] = (char) ((datablock[0] >> 24) & 0xFF);
		data[j+1] = (char) ((datablock[0] >> 16) & 0xFF);
		data[j+2] = (char) ((datablock[0] >> 8) & 0xFF);
		data[j+3] = (char) ((datablock[0]) & 0xFF);
		data[j+4] = (char) ((datablock[1] >> 24) & 0xFF);
		data[j+5] = (char) ((datablock[1] >> 16) & 0xFF);
		data[j+6] = (char) ((datablock[1] >> 8) & 0xFF);
		data[j+7] = (char) ((datablock[1]) & 0xFF);
	}
}

int main()
{
	char data[] = { "1234567890987654321234567890098765432123456789009876543211234567890009876543212" } ;
	uint32_t key[4] = { 0x12345678, 0x12345678, 0x12345678, 0x12345678 };
	uint32_t size = sizeof(data);

	printf("%s\n", data);
		chiffrer(data, size, key);
	printf("%s\n", data);
		dechiffrer(data, size, key);
	printf("%s\n", data);
	return 0;
}
