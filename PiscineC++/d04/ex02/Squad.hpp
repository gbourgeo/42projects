// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Squad.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 21:48:36 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/05 10:21:12 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SQUAD_HPP
# define SQUAD_HPP

# include "ISquad.hpp"

typedef struct		s_units
{
	ISpaceMarine	*marine;
	struct s_units	*next;
}					t_units;

class Squad : public ISquad
{
public:
	Squad();
	Squad(Squad const & src);
	Squad &operator=(Squad const & rhs);
	virtual ~Squad();

	virtual int				getCount() const;
	virtual ISpaceMarine *	getUnit(int) const;
	virtual int				push(ISpaceMarine *);

	t_units *				getUnits() const;

private:
	void					deleteUnits(t_units *unit);
	t_units *			_units;
	int					_nbUnits;
};

#endif
