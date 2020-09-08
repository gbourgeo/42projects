/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:26:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/03 16:28:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Input.hpp"

/*
* Constructor / Destructor
*/
Input::Input(void)
{}

Input::Input(Input const &ref)
{
	if (this != &ref) {
		this->setLastKey(ref.getLastKey());
	}
}

Input::~Input(void) {}

/*
* Getters
*/

int			Input::getLastKey(void) const {
	return this->lastKey;
}

/*
* Setters
*/

void		Input::setLastKey(int c) {
	this->lastKey = c;
}



