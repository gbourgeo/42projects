#include "Ennemy.hpp"

Ennemy::Ennemy():
	AEntities()
{}

Ennemy::Ennemy(char name, int life, int retry, int x, int y, double speed, bool direction):
	AEntities(name, life, retry, x, y, speed, direction)
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
	if (this->getLife() > 0
		&& this->_weapon
		&& this->_weapon->canShoot())
		return this->_weapon->shoot(this->_x, this->_y + 1, false);
	return nullptr;
}
