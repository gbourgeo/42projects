// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/30 17:22:01 by root              #+#    #+#             //
//   Updated: 2018/06/30 19:29:05 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cmath>
#include <iostream>
#include "Fixed.hpp"

Fixed::Fixed(): _value(0)
{
}

Fixed::Fixed(int const raw): _value(raw << this->_nbBits)
{
}

Fixed::Fixed(float const raw): _value(roundf(raw * (1 << this->_nbBits)))
{
}

Fixed::~Fixed()
{
}

Fixed::Fixed(Fixed const & src)
{
	*this = src;
}

Fixed & Fixed::operator=(Fixed const & rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs.getRawBits();
	}
	return *this;
}

Fixed & Fixed::operator++()
{
	this->_value++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed	result(*this);

	++(*this);
	return result;
}

Fixed & Fixed::operator--()
{
	this->_value--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed	result(*this);

	--(*this);
	return result;
}

bool Fixed::operator<(const Fixed & rhs) const
{
	return this->_value < rhs.getRawBits();
}

bool Fixed::operator>(const Fixed & rhs) const
{
	return this->_value > rhs.getRawBits();
}

bool Fixed::operator<=(const Fixed & rhs) const
{
	return !(this->_value > rhs.getRawBits());
}

bool Fixed::operator>=(const Fixed & rhs) const
{
	return !(this->_value < rhs.getRawBits());
}

bool Fixed::operator==(const Fixed & rhs) const
{
	return this->_value == rhs.getRawBits();
}

bool Fixed::operator!=(const Fixed & rhs) const
{
	return !(this->_value == rhs.getRawBits());
}

Fixed Fixed::operator+(const Fixed & rhs) const
{
	Fixed	result;

	result.setRawBits(this->_value + rhs.getRawBits());
	return result;
}

Fixed Fixed::operator-(const Fixed & rhs) const
{
	Fixed	result;

	result.setRawBits(this->_value - rhs.getRawBits());
	return result;
}

Fixed Fixed::operator*(const Fixed & rhs) const
{
	Fixed	result;
	long	overflow;

	overflow = this->_value;
	overflow *= rhs.getRawBits();
	overflow >>= this->_nbBits;
	result.setRawBits(overflow);
	return result;
}

Fixed Fixed::operator/(const Fixed & rhs) const
{
	Fixed	result;
	long	overflow;

	overflow = this->_value;
	overflow <<= this->_nbBits;
	overflow /= rhs.getRawBits();
	result.setRawBits(overflow);
	return result;
}

int Fixed::getRawBits() const
{
	return this->_value;
}

void Fixed::setRawBits(int const raw)
{
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

Fixed & Fixed::min(Fixed & a, Fixed & b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

Fixed & Fixed::max(Fixed & a, Fixed & b)
{
	if (a.getRawBits() > b.getRawBits())
		return a;
	return b;
}

Fixed const & Fixed::min(Fixed const & a, Fixed const & b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

Fixed const & Fixed::max(Fixed const & a, Fixed const & b)
{
	if (a.getRawBits() > b.getRawBits())
		return a;
	return b;
}

std::ostream &	operator<<(std::ostream & o, Fixed const & i)
{
	o << i.toFloat();
	return o;
}
