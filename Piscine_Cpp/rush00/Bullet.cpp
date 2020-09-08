/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bullet.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:36:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/07 14:58:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bullet.hpp"
#include "main.hpp"
#include "PlayerHandler.hpp"
#include "EnnemyHandler.hpp"

Bullet::Bullet():
	Movable(), _name('\0'), _damage(0), _owner(nullptr)
{}

Bullet::Bullet(char name, int x, int y, double speed, int damage, AEntities *owner, bool direction):
	Movable(x, y, speed, direction), _name(name), _damage(damage), _owner(owner)
{}

Bullet::~Bullet()
{}

Bullet::Bullet(Bullet const & src): Movable(src)
{
	*this = src;
}
	
Bullet & Bullet::operator=(Bullet const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_damage = rhs._damage;
		this->_owner = rhs._owner;
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

bool	Bullet::touched(PlayerHandler & p) const
{
	Player			*ptr;
	unsigned int	i;

	i = 1;
	if (dynamic_cast<Player *>(this->_owner) == nullptr)
		while ((ptr = p.getPlayer(i)))
		{
			if (this->getY() == ptr->getY()
				&& this->getX() == ptr->getX()
				&& ptr->getLife() > 0)
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
	Ennemy			*ptr;
	unsigned int	i;

	i = 1;
	if (dynamic_cast<Ennemy *>(this->_owner) == nullptr)
		while ((ptr = e.getEnnemy(i)))
		{
			if (this->getY() == ptr->getY()
				&& this->getX() == ptr->getX()
				&& ptr->getLife() > 0)
			{
				ptr->takeDamage(this->_damage);
				if (this->_owner)
					this->_owner->addScore(this->_damage);
				return true;
			}
			i++;
		}
	return false;
}
