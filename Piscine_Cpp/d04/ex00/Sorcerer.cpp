// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Sorcerer.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 09:34:12 by root              #+#    #+#             //
//   Updated: 2018/07/04 10:54:29 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Sorcerer.hpp"

Sorcerer::Sorcerer()
{}

Sorcerer::Sorcerer(const char * name, const char *title): _name(name), _title(title)
{
	std::cout << _name << ", " << _title << " is born !" << std::endl;
}

Sorcerer::Sorcerer(std::string & name, std::string & title): _name(name), _title(title)
{
	std::cout << _name << ", " << _title << " is born !" << std::endl;
}

Sorcerer::~Sorcerer()
{
	std::cout << _name << ", " << _title << " is dead. Consequences will never be the same !" << std::endl;
}

Sorcerer::Sorcerer(Sorcerer const & src)
{
	*this = src;
}

Sorcerer &Sorcerer::operator=(Sorcerer const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_title = rhs.getTitle();
	}
	return *this;
}

std::string Sorcerer::getName() const
{
	return this->_name;
}

std::string Sorcerer::getTitle() const
{
	return this->_title;
}

void Sorcerer::polymorph(Victim const & victim) const
{
	victim.getPolymorphed();
}

std::ostream & operator<<(std::ostream & os, const Sorcerer & src)
{
	os << "I am " << src.getName() << ", " << src.getTitle() << ", and I like ponies !" << std::endl;
	return os;
}
