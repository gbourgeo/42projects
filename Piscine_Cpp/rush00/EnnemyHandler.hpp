/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EnnemyHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 10:51:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/07 15:11:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENNEMYHANDLER_HPP
# define ENNEMYHANDLER_HPP

# include "BulletHandler.hpp"
# include "Screen.hpp"
# include "Ennemy.hpp"

class Weapon;

typedef struct		s_ennemy
{
	Ennemy				*ennemy;
	struct s_ennemy		*next;
	struct s_ennemy		*prev;
}					t_ennemy;

class EnnemyHandler
{
public:
	EnnemyHandler();
	EnnemyHandler(EnnemyHandler const & src);
	~EnnemyHandler();
	EnnemyHandler & operator=(EnnemyHandler const & rhs);

	void		addEnnemy(char name, int life, int retry, int nb, int y, 
		double speed, Weapon weapon);
	Ennemy		*getEnnemy(unsigned int id);
	void		shoot(BulletHandler & shots);
	void		routine(Screen & screen);
	void		reset();

private:
	void		delEnnemy(t_ennemy *ennemy);

	t_ennemy		*_list;
	unsigned int	_nbEnnemies;
};

#endif
