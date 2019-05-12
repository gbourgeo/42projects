#ifndef GAMEBOARD_HPP
# define GAMEBOARD_HPP

#include <ctime>

class GameBoard
{
public:
	GameBoard(int score, int lives);
	GameBoard(GameBoard const & src);
	~GameBoard();
	GameBoard & operator=(GameBoard const & rhs);

	int		getScore() const;
	time_t	getTiming() const;
	int		getLives() const;
	void	gameStart();
	
private:
	GameBoard();
	int		_score;
	time_t	_timing;
	int		_lives;
};

#endif
