// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AMateria.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 10:38:02 by root              #+#    #+#             //
//   Updated: 2018/07/05 16:12:27 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# define MATERIA_NB		4

# include <string>
# include "ICharacter.hpp"

class AMateria
{
public:
	AMateria(std::string const & type);
	AMateria(AMateria const & src);
	AMateria & operator=(AMateria const & rhs);
	virtual ~AMateria();

	std::string const & getType() const;
	unsigned int		getXP() const;

	virtual AMateria *	clone() const = 0;
	virtual void		use(ICharacter & target);
	
protected:
	AMateria();

	std::string		_type;
	unsigned int	_xp;
};

#endif
