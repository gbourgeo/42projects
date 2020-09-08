// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ICharacter.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 10:48:29 by root              #+#    #+#             //
//   Updated: 2018/07/05 13:18:12 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

class AMateria;

class ICharacter
{
public:
	virtual ~ICharacter() {}
	virtual std::string const &	getName() const = 0;
	virtual void				equip(AMateria * m) = 0;
	virtual void				unequip(int idx) = 0;
	virtual void				use(int idx, ICharacter & target) = 0;
};

#endif
