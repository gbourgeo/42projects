/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:24:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 16:24:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AEntities.hpp"

AEntities::AEntities():
	Movable(), _name('\0'), _life(0), _lifeSave(0), _retry(0), _weapon(0)
{}

AEntities::AEntities(char name, int life, int retry, int x, int y, double speed, bool direction):
	Movable(x, y, speed, direction), _name(name), _life(life), _lifeSave(life), _retry(retry), _weapon(nullptr)
{}

AEntities::~AEntities()
{
	if (this->_weapon != nullptr)
		delete this->_weapon;
}

AEntities::AEntities(AEntities const & src): Movable(src)
{
	*this = src;
}

AEntities & AEntities::operator=(AEntities const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_life = rhs._life;
		this->_lifeSave = rhs._lifeSave;
		this->_retry = rhs._retry;
		this->_weapon = nullptr;
		if (rhs._weapon)
			this->_weapon = new Weapon(*rhs._weapon);
	}
	return *this;
}

char AEntities::getName() const
{
	return this->_name;
}

int AEntities::getLife() const
{
	return this->_life;
}

int AEntities::getRetry() const
{
	return this->_retry;
}

// Weapon *AEntities::getWeapon() const
// {
// 	return this->_weapon;
// }

void AEntities::equip(Weapon *weapon)
{
	if (this->_weapon != nullptr)
		delete this->_weapon;
	this->_weapon = weapon;
}

void AEntities::takeDamage(int value)
{
	this->_life -= value;
	if (this->_life < 0)
		this->_life = 0;
}

void		AEntities::modifyPosition(int x, int y)
{
	if (this->_x == -1)
		this->_x = x;
	else
		this->_x = -1;
	if (this->_y == -1)
		this->_y = y;
	else
		this->_y = -1;
}

void AEntities::deathAnimation()
{
	static int first = 0;
	static struct timeval t1;
	static int x;
	static int y;
	struct timeval t2;
	unsigned long diff;

	if (first == 0)
	{
		x = this->_x;
		y = this->_y;
		modifyPosition(x, y);
		gettimeofday(&t1, NULL);
		first++;
	}
	gettimeofday(&t2, NULL);
	diff = t2.tv_sec * 1000000 - t1.tv_sec * 1000000 + t2.tv_usec - t1.tv_usec;
	if (diff > 300000)
	{
		modifyPosition(x, y);
		gettimeofday(&t1, NULL);
		first++;
	}
	if (first > 7)
	{
		this->_x = this->_xSave;
		this->_y = this->_ySave;
		this->_retry -= 1;
		if (this->_retry > 0)
			this->_life = this->_lifeSave;
		first = 0;
	}
}
