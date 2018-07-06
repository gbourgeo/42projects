// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AsteroBocal.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 00:27:09 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 02:55:06 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AsteroKreog.hpp"

AsteroBocal::AsteroBocal(): _name("AsteroBocal")
{}

AsteroBocal::AsteroBocal(AsteroBocal const & src)
{
	*this = src;
}

AsteroBocal & AsteroBocal::operator=(AsteroBocal const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
	}
	return *this;
}

AsteroBocal::~AsteroBocal()
{}

std::string AsteroBocal::beMined(StripMiner *laser) const
{
	(void)laser;
	return std::string("Flavium");
}

std::string AsteroBocal::beMined(DeepCoreMiner *laser) const
{
	(void)laser;
	return std::string("Thorite");
}

std::string AsteroBocal::getName() const
{
	return this->_name;
}
