// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/30 17:22:01 by root              #+#    #+#             //
//   Updated: 2018/06/30 18:12:18 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Fixed.hpp"

Fixed::Fixed(): _value(0)
{
	std::cout << "Default construstor called" << std::endl;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(Fixed const & src)
{
	std::cout << "Copy construstor called" << std::endl;
	*this = src;
}

Fixed & Fixed::operator=(Fixed const & rhs)
{
	std::cout << "Assignation operator called" << std::endl;
	if (this != &rhs)
	{
		this->_value = rhs.getRawBits();
	}
	return *this;
}

int Fixed::getRawBits() const
{
	std::cout << "getRawBits member function called" << std::endl;
	return this->_value;
}

void Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	this->_value = raw;
}
