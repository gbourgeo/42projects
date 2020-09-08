// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Ice.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 11:07:28 by root              #+#    #+#             //
//   Updated: 2018/07/05 16:25:03 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Ice.hpp"

Ice::Ice(): AMateria("ice")
{}

Ice::Ice(Ice const & src)
{
	*this = src;
}

Ice & Ice::operator=(Ice const & rhs)
{
	if (this != &rhs)
	{
//		this->_type = rhs.getType();
		this->_xp = rhs.getXP();
	}
	return *this;
}

Ice::~Ice()
{}

AMateria *	Ice::clone() const
{
	AMateria	*clone = new Ice(*this);

	return clone;
}

void Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at ";
	AMateria::use(target);
	std::cout << " *" << std::endl;
}
