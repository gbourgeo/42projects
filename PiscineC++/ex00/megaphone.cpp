// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   megaphone.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/28 12:16:32 by root              #+#    #+#             //
//   Updated: 2018/06/28 12:25:56 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

static void	to_upper(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
}

int		main(int ac, char **av)
{
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		while (*++av)
		{
			to_upper(*av);
			std::cout << *av;
		}
		std::cout << std::endl;
	}
	return (0);
}
