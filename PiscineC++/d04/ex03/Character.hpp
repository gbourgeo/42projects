// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Character.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 11:20:59 by root              #+#    #+#             //
//   Updated: 2018/07/05 16:12:20 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <string>
# include "AMateria.hpp"

class Character : public ICharacter
{
public:
	Character(std::string const & name);
	Character(Character const & src);
	Character & operator=(Character const & rhs);
	~Character();

	virtual std::string const &	getName() const;
	virtual void				equip(AMateria * m);
	virtual void				unequip(int idx);
	virtual void				use(int idx, ICharacter & target);
	
	int							getCount() const;
	AMateria *					getMateria(int) const;

private:
	Character();

	std::string		_name;
	int				_count;
	AMateria *		_materia[MATERIA_NB];
};

#endif
