// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AMateria.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 10:42:04 by root              #+#    #+#             //
//   Updated: 2018/07/05 16:52:24 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "AMateria.hpp"

AMateria::AMateria(): _type(""), _xp(0)
{}

AMateria::AMateria(std::string const & type): _type(type), _xp(0)
{}

AMateria::AMateria(AMateria const & src)
{
	*this = src;
}

AMateria & AMateria::operator=(AMateria const & rhs)
{
	if (this != &rhs)
	{
		this->_type = rhs.getType();
		this->_xp = rhs.getXP();
	}
	return *this;
}

AMateria::~AMateria()
{
	this->_type.clear();
	this->_xp = 0;
}

std::string const & AMateria::getType() const
{
	return this->_type;
}

unsigned int AMateria::getXP() const
{
	return this->_xp;
}

void AMateria::use(ICharacter & target)
{
	std::cout << target.getName();
	this->_xp += 10;
}
