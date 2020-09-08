// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Victim.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 10:11:44 by root              #+#    #+#             //
//   Updated: 2018/07/04 10:55:07 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Victim.hpp"

Victim::Victim()
{}

Victim::Victim(const char * name): _name(name)
{
	std::cout << "Some random victim called " << _name << " just popped !" << std::endl;
}

Victim::Victim(std::string & name): _name(name)
{
	std::cout << "Some random victim called " << _name << " just popped !" << std::endl;
}

Victim::~Victim()
{
	std::cout << "Victim " << _name << " just died for no apparent reason !" << std::endl;
}

Victim::Victim(Victim const & src)
{
	*this = src;
}

Victim & Victim::operator=(Victim const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
	}
	return *this;
}

std::string Victim::getName() const
{
	return this->_name;
}

void Victim::getPolymorphed() const
{
	std::cout << _name << " has been turned into a cute little sheep !" << std::endl;
}

std::ostream & operator<<(std::ostream & os, const Victim & src)
{
	os << "I'm " << src.getName() << " and I like otters !" << std::endl;
	return os;
}
