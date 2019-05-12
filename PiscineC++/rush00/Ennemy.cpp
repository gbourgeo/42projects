#include "Ennemy.hpp"

Ennemy::Ennemy():
	AEntities()
{}

Ennemy::Ennemy(char name, int life, int x, int y, double speed, bool direction):
	AEntities(name, life, x, y, speed, direction)
{}

Ennemy::~Ennemy()
{}

Ennemy::Ennemy(Ennemy const & src)
{
	*this = src;
}

Ennemy & Ennemy::operator=(Ennemy const & rhs)
{
	(void)rhs;
	return *this;
}

Bullet *Ennemy::shoot()
{
	if (this->_weapon)
		return this->_weapon->shoot(this->_x, this->_y + 1, false);
	return 0;
}
