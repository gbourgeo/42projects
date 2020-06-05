#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "AEntities.hpp"

class Bullet;

class Player: public AEntities
{
public:
	Player(char name, int life, int retry, int x, int y, double speed, bool direction);
	Player(Player const & src);
	~Player();
	Player & operator=(Player const & rhs);

	Bullet			*shoot();
	unsigned int	getScore() const;

private:
	Player();

	unsigned int	_score;
};

#endif
