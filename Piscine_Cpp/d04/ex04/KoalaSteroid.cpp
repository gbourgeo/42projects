// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   BocalSteroid.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 00:30:55 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 03:01:08 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "KoalaSteroid.hpp"

BocalSteroid::BocalSteroid(): _name("BocalSteroid")
{}

BocalSteroid::BocalSteroid(BocalSteroid const & src)
{
	*this = src;
}

BocalSteroid & BocalSteroid::operator=(BocalSteroid const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
	}
	return *this;
}

BocalSteroid::~BocalSteroid()
{}

std::string BocalSteroid::beMined(StripMiner *laser) const
{
	(void)laser;
	return std::string("Krpite");
}

std::string BocalSteroid::beMined(DeepCoreMiner *laser) const
{
	(void)laser;
	return std::string("Zazium");
}

std::string BocalSteroid::getName() const
{
	return this->_name;
}
