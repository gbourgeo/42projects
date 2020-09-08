// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Enemy.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 11:49:58 by root              #+#    #+#             //
//   Updated: 2018/07/04 13:14:30 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Enemy.hpp"

Enemy::Enemy()
{}

Enemy::Enemy(int hp, std::string const & type): _hp(hp), _type(type)
{}

Enemy::Enemy(Enemy const & src)
{
	*this = src;
}

Enemy & Enemy::operator=(Enemy const & rhs)
{
	if (this != &rhs)
	{
	}
	return *this;
}

Enemy::~Enemy()
{}

std::string Enemy::getType() const
{
	return this->_type;
}

int Enemy::getHP() const
{
	return this->_hp;
}

void Enemy::takeDamage(int damage)
{
	if (damage > 0) {
		this->_hp = (damage > this->_hp) ? 0 : this->_hp - damage;
	}
		
}
