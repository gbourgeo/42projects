// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Character.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 11:22:09 by root              #+#    #+#             //
//   Updated: 2018/07/05 17:29:42 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
#include <iostream>
#include "Character.hpp"

Character::Character(): _name(""), _count(0)
{
	for (int i = 0; i < MATERIA_NB; i++) {
		this->_materia[i] = 0;
	}
}

Character::Character(std::string const & name): _name(name), _count(0)
{
	for (int i = 0; i < MATERIA_NB; i++) {
		this->_materia[i] = 0;
	}
}

Character::Character(Character const & src)
{
	*this = src;
}

Character & Character::operator=(Character const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_count = rhs.getCount();
		for (int i = 0; i < MATERIA_NB; i++) {
			if (i < this->_count)
				this->_materia[i] = rhs.getMateria(i)->clone();
			else
				this->_materia[i] = 0;
		}
	}
	return *this;
}

Character::~Character()
{
	std::cout << this->_name << " " << this->_count << std::endl;
	this->_name.clear();
	for (int i = 0; i < this->_count; i++) {
		if (this->_materia[i])
			delete this->_materia[i];
		this->_materia[i] = 0;
	}
	this->_count = 0;
}

std::string const & Character::getName() const
{
	return this->_name;
}

void Character::equip(AMateria * m)
{
	if (this->_count >= MATERIA_NB)
		return ;
	this->_materia[this->_count++] = m;
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= MATERIA_NB)
		return ;
	while (idx + 1 < MATERIA_NB) {
		this->_materia[idx] = this->_materia[idx + 1];
		idx++;
	}
	this->_materia[idx] = 0;
	this->_count--;
}

void Character::use(int idx, ICharacter & target)
{
	if (idx < 0 || idx >= MATERIA_NB || this->_materia[idx] == 0)
		return ;
	this->_materia[idx]->use(target);
}

int Character::getCount() const
{
	return this->_count;
}

AMateria * Character::getMateria(int idx) const
{
	if (idx < 0 || idx >= MATERIA_NB)
		return 0;
	return this->_materia[idx];
}
