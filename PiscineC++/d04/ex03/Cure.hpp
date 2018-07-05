// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Cure.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 11:05:50 by root              #+#    #+#             //
//   Updated: 2018/07/05 16:16:34 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CURE_HPP
# define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria
{
public:
	Cure();
	Cure(Cure const & src);
	Cure & operator=(Cure const & rhs);
	~Cure();

	virtual AMateria *	clone() const;
	virtual void		use(ICharacter & target);
};

#endif
