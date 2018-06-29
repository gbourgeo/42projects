// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Phonebook.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/28 12:30:48 by root              #+#    #+#             //
//   Updated: 2018/06/28 14:30:54 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Contact.hpp"

static void	add_contact(Contact contact[], int &i)
{
	if (i >= 8) {
		std::cout << "Maximum contact reached..." << std::endl;
		return;
	}
	contact[i].set_info();
	i += 1;
}

static void	search_contact(Contact contact[], const int &i)
{
	std::string	nb;
	int			j = 0;

	std::cout << " ___________________________________________" << std::endl;
	std::cout << "|     index|first name| last name|  nickname|" << std::endl;
	while (j < i)
	{
		std::cout << "|         " << j;
		contact[j].show_min_info();
		j++;
	}
	if (j)
	{
		std::cout << std::endl << "Index : ";
		std::cin >> j;
		if (std::cin.fail() || j < 0 || j >= i) {
			std::cin.clear();
			std::cout << "Wrong number !" << std::endl;
		}
		else
			contact[j].show_full_info();
	}
}

int			main()
{
	Contact		contact[8];
	std::string	command;
	int			i;

	i = 0;
	while (1)
	{
		std::getline(std::cin, command);
		if (command.compare("EXIT") == 0)
			break ;
		if (command.compare("ADD") == 0)
			add_contact(contact, i);
		if (command.compare("SEARCH") == 0)
			search_contact(contact, i);
	}
	return (0);
}
