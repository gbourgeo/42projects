#include "AEntities.hpp"

AEntities::AEntities():
	Movable(), _name('\0'), _life(0), _weapon(0)
{}

AEntities::AEntities(char name, int life, int x, int y, double speed, bool direction):
	Movable(x, y, speed, direction), _name(name), _life(life), _bdirection(direction), _weapon(0)
{}

AEntities::~AEntities()
{}

AEntities::AEntities(AEntities const & src)
{
	*this =src;
}

AEntities & AEntities::operator=(AEntities const & rhs)
{
	if (this != &rhs)
	{
		this->_life = rhs.getLife();
		this->_x = rhs.getX();
		this->_y = rhs.getY();
		this->_weapon = rhs.getWeapon();
	}
	return *this;
}

char AEntities::getName() const
{
	return this->_name;
}

int AEntities::getLife() const
{
	return this->_life;
}

Weapon *AEntities::getWeapon() const
{
	return this->_weapon;
}

void AEntities::equip(Weapon *weapon)
{
	this->_weapon = weapon;
}

void AEntities::takeDamage(int value)
{
	this->_life -= value;
	if (this->_life < 0)
		this->_life = 0;
}
