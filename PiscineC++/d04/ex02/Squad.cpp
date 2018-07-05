// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Squad.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 22:00:22 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/04 22:33:09 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Squad.hpp"

Squad::Squad(): _units(0), _nbUnits(0)
{}

Squad::Squad(Squad const & src)
{
	*this = src;
}

Squad & Squad::operator=(Squad const & rhs)
{
	if (this != &rhs)
	{
		this->_units = rhs.getUnits();
		this->_nbUnits = rhs.getCount();
	}
	return *this;
}

Squad::~Squad()
{
	Squad::deleteUnits(this->_units);
}

void Squad::deleteUnits(t_units *unit)
{
	if (unit)
		Squad::deleteUnits(unit->next);
	delete unit->marine;
	unit->marine = 0;
	unit->next = 0;
	delete unit;
}

int Squad::getCount() const
{
	return this->_nbUnits;
}

ISpaceMarine *Squad::getUnit( int pos ) const
{
	t_units		*ptr;

	if (pos < 0 || pos >= this->_nbUnits || this->_units == 0)
		return 0;
	ptr = this->_units;
	while (pos-- > 0) {
		ptr = ptr->next;
	}
	return ptr->marine;
}

int Squad::push(ISpaceMarine *marine)
{
	t_units		*ptr;

	ptr = this->_units;
	if (marine == 0)
		return this->_nbUnits;
	if (this->_units == 0) {
		this->_units = new t_units;
		this->_units->marine = marine;
		this->_units->next = 0;
		return ++this->_nbUnits;
	}
	while (ptr && ptr->next) {
		if (marine == ptr->marine)
			return this->_nbUnits;
		ptr = ptr->next;
	}
	if (marine == ptr->marine)
		return this->_nbUnits;
	ptr->next = new t_units;
	ptr->next->marine = marine;
	ptr->next->next = 0;
	return ++this->_nbUnits;
}
