// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Peon.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 10:23:35 by root              #+#    #+#             //
//   Updated: 2018/07/04 11:07:11 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Peon.hpp"

Peon::Peon()
{}

Peon::Peon(const char *name): Victim(name)
{
	std::cout << "Zog zog." << std::endl;
}

Peon::Peon(std::string & name): Victim(name)
{
	std::cout << "Zog zog." << std::endl;
}

Peon::~Peon()
{
	std::cout << "Bleuark..." << std::endl;
}

Peon::Peon(Peon const & src)
{
	*this = src;
}

Peon & Peon::operator=(Peon const & src)
{
	if (this != &src)
	{
		this->_name = src.getName();
	}
	return *this;
}

void Peon::getPolymorphed() const
{
	std::cout << this->_name << " has been turned into a pink pony !" << std::endl;
}
