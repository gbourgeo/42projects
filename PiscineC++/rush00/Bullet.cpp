/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bullet.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:36:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 16:22:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bullet.hpp"
#include "main.hpp"
#include "PlayerHandler.hpp"
#include "EnnemyHandler.hpp"

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
		this->_name = rhs._name;
		this->_damage = rhs._damage;
	}
	return *this;
}

bool Bullet::isOut() const {
	return this->getY() <= 2 || this->getY() >= HEIGHT - 1;
}

char Bullet::getName() const
{
	return this->_name;
}

// int Bullet::getDamage() const
// {
// 	return this->_damage;
// }

bool	Bullet::touched(PlayerHandler & p) const
{
	Player			*ptr;
	unsigned int	i;

	i = 1;
	while ((ptr = p.getPlayer(i)))
	{
		if (this->getY() == ptr->getY() && this->getX() == ptr->getX() && ptr->getLife() > 0)
		{
			ptr->takeDamage(this->_damage);
			return true;
		}
		i++;
	}
	return false;
}

bool	Bullet::touched(EnnemyHandler & e) const
{
	Ennemy		*ptr;
	unsigned int	i;

	i = 1;
	while ((ptr = e.getEnnemy(i)))
	{
		if (this->getY() == ptr->getY() && this->getX() == ptr->getX())
		{
			ptr->takeDamage(this->_damage);
			return true;
		}
		i++;
	}
	return false;
}
