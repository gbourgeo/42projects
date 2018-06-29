// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 21:25:38 by root              #+#    #+#             //
//   Updated: 2018/06/29 21:32:59 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <fstream>

static void	read_stdin()
{
	std::string	buff;

	while (getline(std::cin, buff))
	{
		std::cout << buff << std::endl;
	}
}

static void	read_files(char **av)
{
	std::size_t		i = 1;
	std::string		buff;
	std::ifstream	file;

	while (av[i])
	{
		file.open(av[i]);
		if (!file.is_open()) {
			std::cout << "Can't open file " << av[i] << std::endl;
			continue ;
		}
		while (getline(file, buff))
		{
			std::cout << buff << std::endl;
		}
		file.close();
		i++;
	}
}

int			main(int ac, char **av)
{
	if (ac == 1)
		read_stdin();
	else
		read_files(av);
	return 0;
}
