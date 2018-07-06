// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   DeepCoreMiner.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 22:48:43 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 03:10:54 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "DeepCoreMiner.hpp"

DeepCoreMiner::DeepCoreMiner()
{}

DeepCoreMiner::DeepCoreMiner(DeepCoreMiner const & src)
{
	*this = src;
}

DeepCoreMiner & DeepCoreMiner::operator=(DeepCoreMiner const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

DeepCoreMiner::~DeepCoreMiner()
{}

void DeepCoreMiner::mine(IAsteroid *asteroid)
{
	if (asteroid) {
		std::cout << "* mining deep ... got ";
		std::cout << asteroid->beMined(this);
		std::cout << " ! *" << std::endl;
	}
}
