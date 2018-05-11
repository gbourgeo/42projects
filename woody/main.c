/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 00:07:22 by root              #+#    #+#             */
/*   Updated: 2018/05/07 00:12:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <stdio.h>

void encrypt(unsigned char *data, unsigned int len, const uint32_t *k);
void decrypt(unsigned char *data, unsigned int len, const uint32_t *k);

int main()
{
	unsigned char data[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const uint32_t k[] = {0x95a8882c, 0x9d2cc113, 0x815aa0cd, 0xa1c489f7};

	printf("%s %ld\n", data, sizeof(data));
	encrypt(data, sizeof(data), k);
	printf("%s\n", data);
	decrypt(data, sizeof(data), k);
	printf("%s\n", data);
}
