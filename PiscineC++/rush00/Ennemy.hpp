#ifndef ENNEMY_HPP
# define ENNEMY_HPP

//#include "main.hpp"
#include "AEntities.hpp"

class Bullet;

class Ennemy: public AEntities
{
public:
	Ennemy(char name, int life, int x, int y, double speed, bool direction);
	Ennemy(Ennemy const & src);
	~Ennemy();
	Ennemy & operator=(Ennemy const & rhs);

	Bullet		*shoot();

private:
	Ennemy();	
};

#endif
