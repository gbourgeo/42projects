// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Victim.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 10:10:00 by root              #+#    #+#             //
//   Updated: 2018/07/04 10:54:55 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VICTIM_HPP
# define VICTIM_HPP

#include <iostream>
#include <string>

class Victim
{
public:
	Victim(const char *name);
	Victim(std::string & name);
	Victim(Victim const & src);
	virtual Victim & operator=(Victim const & rhs);
	virtual ~Victim();

	std::string		getName() const;
	virtual void			getPolymorphed() const;

protected:
	Victim();

	std::string		_name;
};

std::ostream & operator<<(std::ostream & os, const Victim & src);

#endif
