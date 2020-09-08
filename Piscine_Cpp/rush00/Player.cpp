#include "Player.hpp"

Player::Player():
	AEntities()
{}

Player::Player(char name, int life, int retry, int x, int y, double speed, bool direction):
	AEntities(name, life, retry, x, y, speed, direction)
{}

Player::~Player()
{}

Player::Player(Player const & src): AEntities(src)
{
	*this = src;
}

Player & Player::operator=(Player const & rhs)
{
	if (this != &rhs)
	{
		this->_score = rhs._score;
	}
	return *this;
}

Bullet *Player::shoot()
{
	if (this->_weapon)
		return this->_weapon->shoot(this->_x, this->_y - 1, true);
	return 0;
}

unsigned int Player::getScore() const
{
	return this->_score;
}