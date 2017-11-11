// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   common.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/05 20:39:17 by root              #+#    #+#             //
//   Updated: 2017/11/05 22:42:08 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef COMMON_HPP
# define COMMON_HPP

# define DAEMON_BUFF	512
# define DAEMON_MAGIC	0xDAE1

typedef struct	s_hdr
{
	int			magic;
	int			crypted;
	char		data[DAEMON_BUFF];
}				t_hdr;

int		Base64decode_len(const char *bufcoded);
int		Base64decode(char *bufplain, const char *bufcoded);
int		Base64encode_len(int len);
int		Base64encode(char *encoded, const char *string, int len);

#endif
