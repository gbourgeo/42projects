// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bullet.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/06 16:36:37 by gbourgeo          #+#    #+#             //
//   Updated: 2018/10/06 20:02:38 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bullet.hpp"
#include "main.hpp"

Bullet::Bullet():
	Movable(), _name('\0'), _damage(0)
{}

Bullet::Bullet(char name, int x, int y, double speed, int damage, bool direction):
	Movable(x, y, speed, direction), _name(name), _damage(damage)
{}

Bullet::~Bullet()
{}

Bullet::Bullet(Bullet const & src)
{
	*this = src;
}
	
Bullet & Bullet::operator=(Bullet const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_damage = rhs.getDamage();
	}
	return *this;
}

bool Bullet::isArrived() const {
	return this->getY() <= 1 || this->getY() >= HEIGHT;
}

char Bullet::getName() const
{
	return this->_name;
}

int Bullet::getDamage() const
{
	return this->_damage;
}
