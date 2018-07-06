// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StripMiner.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 23:28:13 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 03:11:09 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "StripMiner.hpp"

StripMiner::StripMiner()
{}

StripMiner::StripMiner(StripMiner const & src)
{
	*this = src;
}

StripMiner & StripMiner::operator=(StripMiner const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

StripMiner::~StripMiner()
{}

void StripMiner::mine(IAsteroid *asteroid)
{
	if (asteroid) {
		std::cout << "* strip mining ... got ";
		std::cout << asteroid->beMined(this);
		std::cout << " ! *" << std::endl;
	}
}
