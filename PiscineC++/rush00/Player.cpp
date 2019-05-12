#include "Player.hpp"

Player::Player():
	AEntities()
{}

Player::Player(char name, int life, int x, int y, double speed, bool direction):
	AEntities(name, life, x, y, speed, direction)
{}

Player::Player(Player const & src)
{
	*this = src;
}

Player::~Player()
{}

Player & Player::operator=(Player const & rhs)
{
	(void)rhs;
	return *this;
}

Bullet *Player::shoot()
{
	if (this->_weapon)
		return this->_weapon->shoot(this->_x, this->_y - 1, true);
	return 0;
}
