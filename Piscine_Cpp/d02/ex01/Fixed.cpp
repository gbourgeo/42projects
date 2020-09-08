// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/30 17:22:01 by root              #+#    #+#             //
//   Updated: 2018/06/30 18:20:32 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cmath>
#include <iostream>
#include "Fixed.hpp"

Fixed::Fixed(): _value(0)
{
	std::cout << "Default construstor called" << std::endl;
}

Fixed::Fixed(int const raw): _value(raw << this->_nbBits)
{
	std::cout << "Int construstor called" << std::endl;
}

Fixed::Fixed(float const raw): _value(roundf(raw * (1 << this->_nbBits)))
{
	std::cout << "Float construstor called" << std::endl;
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
//	std::cout << "getRawBits member function called" << std::endl;
	return this->_value;
}

void Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	this->_value = raw;
}

float Fixed::toFloat() const
{
	return this->_value / (float)(1 << this->_nbBits);
}


int Fixed::toInt() const
{
	return this->_value >> this->_nbBits;
}

std::ostream &	operator<<(std::ostream & o, Fixed const & i)
{
	o << i.toFloat();
	return o;
}
