/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 14:58:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/07 14:11:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon():
	_shootRate(0.0), _bulletSpeed(0.0), _bulletName('\0'), _bulletDamage(0), _owner(nullptr)
{
	this->setLastShot();
}

Weapon::Weapon(double shootRate, double bulletSpeed, char bulletName, int bulletDamage):
	_shootRate(shootRate),
	_bulletSpeed(bulletSpeed),
	_bulletName(bulletName),
	_bulletDamage(bulletDamage),
	_owner(nullptr)
{
	this->setLastShot();
}

Weapon::~Weapon()
{}

Weapon::Weapon(Weapon const & src)
{
	*this = src;
}

Weapon & Weapon::operator=(Weapon const & rhs)
{
	if (this != &rhs)
	{
		this->_shootRate = rhs._shootRate;
		this->_bulletSpeed = rhs._bulletSpeed;
		this->_bulletName = rhs._bulletName;
		this->_bulletDamage = rhs._bulletDamage;
		this->_lastShot = rhs._lastShot;
		this->_owner = rhs._owner; // ???
	}
	return *this;
}

void Weapon::setOwner(AEntities *owner)
{
	this->_owner = owner;
}

bool Weapon::canShoot(void) const {
	timeval current;

	gettimeofday(&current, NULL);
	unsigned long diff = current.tv_sec * 1000000
		- this->_lastShot.tv_sec * 1000000
		+ current.tv_usec
		- this->_lastShot.tv_usec;
	return diff > (1000000.0 * this->_shootRate) ? true : false;
}

Bullet *Weapon::shoot(int x, int y, bool direction)
{
	this->setLastShot();
	return new Bullet(this->_bulletName,
		x, y,
		this->_bulletSpeed,
		this->_bulletDamage,
		this->_owner,
		direction);
}

void	Weapon::setLastShot(void) {
	gettimeofday(&this->_lastShot, NULL);
}
