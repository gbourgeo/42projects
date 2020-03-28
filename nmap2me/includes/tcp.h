
#ifndef TCP_H
# define TCP_H

/*
** 96 bit (12 bytes) pseudo header needed for tcp header checksum calculation
*/
struct			pseudo_header
{
	u_int32_t	source_address;
	u_int32_t	dest_address;
	u_int8_t	placeholder;
	u_int8_t	protocol;
	u_int16_t	length;
};

#endif
