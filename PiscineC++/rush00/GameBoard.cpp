#include "GameBoard.hpp"

GameBoard::GameBoard():
	_score(0), _timing(0), _lives(0)
{}

GameBoard::GameBoard(int score, int lives):
	_score(score), _timing(time(0)), _lives(lives)
{}

GameBoard::GameBoard(GameBoard const & src)
{
	*this = src;
}

GameBoard::~GameBoard()
{}

GameBoard & GameBoard::operator=(GameBoard const & rhs)
{
	if (this != &rhs)
	{
		this->_score = rhs.getScore();
		this->_timing = rhs.getTiming();
		this->_lives = rhs.getLives();
	}
	return *this;
}

int GameBoard::getScore() const
{
	return this->_score;
}

time_t GameBoard::getTiming() const
{
	return this->_timing;
}

int GameBoard::getLives() const
{
	return this->_lives;
}

void GameBoard::gameStart()
{
	time(&this->_timing);
}
