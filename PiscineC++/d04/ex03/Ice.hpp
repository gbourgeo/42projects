// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Ice.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 11:05:50 by root              #+#    #+#             //
//   Updated: 2018/07/05 11:12:03 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ICE_HPP
# define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria
{
public:
	Ice();
	Ice(Ice const & src);
	Ice & operator=(Ice const & rhs);
	~Ice();

	virtual AMateria *	clone() const;
	virtual void		use(ICharacter & target);
};

#endif
