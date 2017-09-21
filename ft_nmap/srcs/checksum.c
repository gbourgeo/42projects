/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 21:00:09 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/14 21:00:12 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

unsigned short		checksum(unsigned short *ptr, int nbytes)
{
	register long sum;
	    unsigned short oddbyte;
	    register short answer;

	    sum=0;
	    while(nbytes>1) {
	        sum+=*ptr++;
	        nbytes-=2;
	    }
	    if(nbytes==1) {
	        oddbyte=0;
	        *((u_char*)&oddbyte)=*(u_char*)ptr;
	        sum+=oddbyte;
	    }

	    sum = (sum>>16)+(sum & 0xffff);
	    sum = sum + (sum>>16);
	    answer=(short)~sum;

	    return(answer);
}
