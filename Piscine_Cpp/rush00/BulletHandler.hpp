/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BulletHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 13:43:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/07 15:29:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULLETHANDLER_HPP
# define BULLETHANDLER_HPP

# include "Bullet.hpp"
# include "Screen.hpp"

class PlayerHandler;
class EnnemyHandler;

typedef struct		s_shot
{
	Bullet			*shot;
	struct s_shot	*next;
	struct s_shot	*prev;
}					t_shot;

class BulletHandler
{
public:
	BulletHandler();
	~BulletHandler();
	BulletHandler(BulletHandler const & src);
	BulletHandler & operator=(BulletHandler const & rhs);

	void		addShot(Bullet *b);
	void		moveShots(Screen & screen, PlayerHandler & p, EnnemyHandler & e);
	void		reset();

private:
	void		updateShots(PlayerHandler & p, EnnemyHandler & e);
	t_shot		*_shots;
};

#endif
