// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   contact.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/28 12:46:39 by root              #+#    #+#             //
//   Updated: 2018/06/28 14:23:56 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Contact.hpp"
#include <iostream>

Contact::Contact()
{}

Contact::~Contact()
{}

void Contact::set_info()
{
	std::cout << "First Name: ";
	std::getline(std::cin, this->first_name);
	std::cout << "Last Name: ";
	std::getline(std::cin, this->last_name);
	std::cout << "Nickname: ";
	std::getline(std::cin, this->nick_name);
	std::cout << "Login: ";
	std::getline(std::cin, this->login);
	std::cout << "Postal Address: ";
	std::getline(std::cin, this->postal_address);
	std::cout << "Email Address: ";
	std::getline(std::cin, this->email_address);
	std::cout << "Phone Number: ";
	std::getline(std::cin, this->phone_number);
	std::cout << "Birthday Date: ";
	std::getline(std::cin, this->birthday_date);
	std::cout << "Favorite Meal: ";
	std::getline(std::cin, this->favorite_meal);
	std::cout << "Underwear Color: ";
	std::getline(std::cin, this->underwear_color);
	std::cout << "Darkest Secret: ";
	std::getline(std::cin, this->darkest_secret);
}

void Contact::show_min_info()
{
	std::cout << "|";
	if (this->first_name.size() <= 10) {
		int i = 0;
		while (i + this->first_name.size() < 10) {
			std::cout << ' ';
			i++;
		}
		std::cout << this->first_name;
	} else {
		int i = 0;
		while (i < 9) {
			std::cout << this->first_name[i];
			i++;
		}
		std::cout << '.';
	}
	std::cout << "|";
	if (this->last_name.size() <= 10) {
		int i = 0;
		while (i + this->last_name.size() < 10) {
			std::cout << ' ';
			i++;
		}
		std::cout << this->last_name;
	} else {
		int i = 0;
		while (i < 9) {
			std::cout << this->last_name[i];
			i++;
		}
		std::cout << '.';
	}
	std::cout << "|";
	if (this->nick_name.size() <= 10) {
		int i = 0;
		while (i + this->nick_name.size() < 10) {
			std::cout << ' ';
			i++;
		}
		std::cout << this->nick_name;
	} else {
		int i = 0;
		while (i < 9) {
			std::cout << this->nick_name[i];
			i++;
		}
		std::cout << '.';
	}
	std::cout << "|";
	std::cout << std::endl;
}

void Contact::show_full_info()
{
	std::cout << "First Name: ";
	std::cout << this->first_name << std::endl;
	std::cout << "Last Name: ";
	std::cout << this->last_name << std::endl;
	std::cout << "Nickname: ";
	std::cout << this->nick_name << std::endl;
	std::cout << "Login: ";
	std::cout << this->login << std::endl;
	std::cout << "Postal Address: ";
	std::cout << this->postal_address << std::endl;
	std::cout << "Email Address: ";
	std::cout << this->email_address << std::endl;
	std::cout << "Phone Number: ";
	std::cout << this->phone_number << std::endl;
	std::cout << "Birthday Date: ";
	std::cout << this->birthday_date << std::endl;
	std::cout << "Favorite Meal: ";
	std::cout << this->favorite_meal << std::endl;
	std::cout << "Underwear Color: ";
	std::cout << this->underwear_color << std::endl;
	std::cout << "Darkest Secret: ";
	std::cout << this->darkest_secret << std::endl;
}
