// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MateriaSource.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 15:59:19 by root              #+#    #+#             //
//   Updated: 2018/07/05 17:06:48 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MateriaSource.hpp"

MateriaSource::MateriaSource(): _count(0)
{
	for (int i = 0; i < MATERIA_NB; i++) {
		this->_materia[i] = 0;
	}
}

MateriaSource::MateriaSource(MateriaSource const & src)
{
	*this = src;
}

MateriaSource & MateriaSource::operator=(MateriaSource const & rhs)
{
	if (this != &rhs)
	{
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

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < this->_count; i++) {
		if (this->_materia[i])
			delete this->_materia[i];
		this->_materia[i] = 0;
	}
	this->_count = 0;
}

int MateriaSource::getCount() const
{
	return this->_count;
}

AMateria * MateriaSource::getMateria(int idx) const
{
	if (idx < 0 || idx >= MATERIA_NB)
		return 0;
	return this->_materia[idx];
}

void MateriaSource::learnMateria(AMateria * m)
{
	if (m == 0 || this->_count >= MATERIA_NB)
		return ;
	this->_materia[this->_count++] = m;
}

AMateria * MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < this->_count; i++) {
		if (this->_materia[i]->getType() == type)
			return this->_materia[i]->clone();
	}
	return 0;
}
