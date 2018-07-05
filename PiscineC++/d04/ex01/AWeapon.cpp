// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AWeapon.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 11:20:19 by root              #+#    #+#             //
//   Updated: 2018/07/04 13:13:29 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AWeapon.hpp"

AWeapon::AWeapon()
{}

AWeapon::AWeapon(std::string const & name, int apcost, int damage):
	_name(name), _apcost(apcost), _damage(damage)
{}

AWeapon::~AWeapon()
{}

AWeapon::AWeapon(AWeapon const & src)
{
	*this = src;
}

AWeapon & AWeapon::operator=(AWeapon const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_apcost = rhs.getAPCost();
		this->_damage = rhs.getDamage();
	}
	return *this;
}

std::string AWeapon::getName() const
{
	return this->_name;
}

int AWeapon::getAPCost() const
{
	return this->_apcost;
}

int AWeapon::getDamage() const
{
	return this->_damage;
}
