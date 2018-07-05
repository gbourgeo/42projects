// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MateriaSource.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 15:58:08 by root              #+#    #+#             //
//   Updated: 2018/07/05 16:21:37 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
public:
	MateriaSource();
	MateriaSource(MateriaSource const & src);
	MateriaSource & operator=(MateriaSource const & rhs);
	~MateriaSource();

	void		learnMateria(AMateria*);
	AMateria *	createMateria(std::string const & type);

	int			getCount() const;
	AMateria *	getMateria(int idx) const;

private:
	int				_count;
	AMateria *		_materia[MATERIA_NB];
	
};

#endif
