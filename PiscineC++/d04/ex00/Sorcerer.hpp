// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Sorcerer.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 09:32:33 by root              #+#    #+#             //
//   Updated: 2018/07/04 10:54:13 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SORCERER_HPP
# define SORCERER_HPP

#include <iostream>
#include <string>
#include "Victim.hpp"

class Sorcerer
{

public:
	Sorcerer(const char * name, const char * title);
	Sorcerer(std::string & name, std::string & title);
	Sorcerer(Sorcerer const & src);
	Sorcerer & operator=(Sorcerer const & rhs);
	~Sorcerer();

	std::string		getName() const;
	std::string		getTitle() const;
	void			polymorph(Victim const & victim) const;

private:
	Sorcerer();

	std::string		_name;
	std::string		_title;
};

std::ostream & operator<<(std::ostream & os, const Sorcerer & src);

#endif
