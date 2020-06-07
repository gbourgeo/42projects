#ifndef AENTITIES_HPP
# define AENTITIES_HPP

# include "Movable.hpp"
# include "Weapon.hpp"
# include "Bullet.hpp"

class AEntities: public Movable
{
public:
	AEntities(char name, int life, int retry, int x, int y, double speed, bool direction);
	AEntities(AEntities const & src);
	virtual ~AEntities() = 0;
	AEntities & operator=(AEntities const & rhs);

	char				getName() const;
	int					getLife() const;
	int					getRetry() const;
	void				addScore(int score);
	void				equip(Weapon *weapon);
	virtual Bullet		*shoot() = 0;
	void				takeDamage(int value);
	void				deathAnimation();

protected:
	AEntities();
	void				modifyPosition(int x, int y);

	char			_name;
	int				_life;
	int				_lifeSave;
	int				_retry;
	unsigned int	_score;
	Weapon			*_weapon;
};

#endif
