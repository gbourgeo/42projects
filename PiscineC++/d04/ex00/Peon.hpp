// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Peon.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 10:23:40 by root              #+#    #+#             //
//   Updated: 2018/07/04 10:55:24 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PEON_HPP
# define PEON_HPP

#include "Victim.hpp"

class Peon: public Victim
{
public:
	Peon(const char *name);
	Peon(std::string &name);
	Peon(Peon const & src);
	virtual Peon & operator=(Peon const & src);
	virtual ~Peon();

	virtual void	getPolymorphed() const;
private:
	Peon();
};

#endif
