// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Cure.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 11:07:28 by root              #+#    #+#             //
//   Updated: 2018/07/05 16:42:51 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Cure.hpp"

Cure::Cure(): AMateria("cure")
{}

Cure::Cure(Cure const & src)
{
	*this = src;
}

Cure & Cure::operator=(Cure const & rhs)
{
	if (this != &rhs)
	{
//		this->_type = rhs.getType();
		this->_xp = rhs.getXP();
	}
	return *this;
}

Cure::~Cure()
{}

AMateria *	Cure::clone() const
{
	AMateria	*clone = new Cure(*this);

	return clone;
}

void Cure::use(ICharacter& target)
{
	std::cout << "* heals ";
	AMateria::use(target);
	std::cout << "'s wounds *" << std::endl;
}
