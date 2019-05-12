// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Weapon.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/06 14:58:29 by gbourgeo          #+#    #+#             //
//   Updated: 2018/10/07 03:13:01 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Weapon.hpp"

Weapon::Weapon():
	_shootRate(0), _bulletSpeed(0), _bulletName(0), _bulletDamage(0)
{
	this->setLastShot();
}

Weapon::Weapon(double shootRate, double bulletSpeed, char bulletName, int bulletDamage):
	_shootRate(shootRate),
	_bulletSpeed(bulletSpeed),
	_bulletName(bulletName),
	_bulletDamage(bulletDamage)
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
		this->_shootRate = rhs.getShootRate();
		this->_bulletSpeed = rhs.getBulletSpeed();
		this->_bulletName = rhs.getBulletName();
		this->_bulletDamage = rhs.getBulletDamage();
		this->_lastShot = rhs.getLastShot();
	}
	return *this;
}

double Weapon::getShootRate() const
{
	return this->_shootRate;
}

double Weapon::getBulletSpeed() const
{
	return this->_bulletSpeed;
}

char Weapon::getBulletName() const
{
	return this->_bulletName;
}

int Weapon::getBulletDamage() const
{
	return this->_bulletDamage;
}

bool Weapon::canShoot(void) const {
	timeval current;
	gettimeofday(&current, NULL);
	timeval last = this->getLastShot();

    int diff = (((current.tv_sec - last.tv_sec) * 1000000) +
            (current.tv_usec - last.tv_usec))/1000;

	return diff > (this->getShootRate() * 1000) ? true : false;
}

Bullet *Weapon::shoot(int x, int y, bool direction)
{
	this->setLastShot();
	return new Bullet(this->_bulletName, x, y, this->_bulletSpeed, this->_bulletDamage, direction);
	
}

timeval Weapon::getLastShot() const
{
	return this->_lastShot;
}

void	Weapon::setLastShot(void) {
	timeval now;
	gettimeofday(&now, NULL);
	this->_lastShot = now;
}
