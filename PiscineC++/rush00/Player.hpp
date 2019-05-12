#ifndef PLAYER_HPP
# define PLAYER_HPP

//#include "main.hpp"
#include "AEntities.hpp"

class Bullet;

class Player: public AEntities
{
public:
	Player(char name, int life, int x, int y, double speed, bool direction);
	Player(Player const & src);
	~Player();
	Player & operator=(Player const & rhs);

	Bullet		*shoot();

private:
	Player();
};

#endif
