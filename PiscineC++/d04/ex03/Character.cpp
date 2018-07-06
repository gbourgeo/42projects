// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Character.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 11:22:09 by root              #+#    #+#             //
//   Updated: 2018/07/05 22:38:06 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Character.hpp"

Character::Character(): _name("")
{
	for (int i = 0; i < MATERIA_NB; i++) {
		this->_materia[i] = 0;
	}
}

Character::Character(std::string const & name): _name(name)
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
		for (int i = 0; i < MATERIA_NB; i++) {
			if (this->_materia[i])
				this->_materia[i] = rhs.getMateria(i)->clone();
			else
				this->_materia[i] = 0;
		}
	}
	return *this;
}

Character::~Character()
{
	this->_name.clear();
	for (int i = 0; i < MATERIA_NB; i++) {
		if (this->_materia[i])
			delete this->_materia[i];
		this->_materia[i] = 0;
	}
}

std::string const & Character::getName() const
{
	return this->_name;
}

void Character::equip(AMateria * m)
{
	for (int i = 0; i < MATERIA_NB; i++) {
		if (this->_materia[i] == 0) {
			this->_materia[i] = m;
			break ;
		}
	}
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= MATERIA_NB)
		return ;
	this->_materia[idx] = 0;
}

void Character::use(int idx, ICharacter & target)
{
	if (idx < 0 || idx >= MATERIA_NB || this->_materia[idx] == 0)
		return ;
	this->_materia[idx]->use(target);
}

AMateria * Character::getMateria(int idx) const
{
	if (idx < 0 || idx >= MATERIA_NB)
		return 0;
	return this->_materia[idx];
}
