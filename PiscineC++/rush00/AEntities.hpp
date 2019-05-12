#ifndef AENTITIES_HPP
# define AENTITIES_HPP

//#include "main.hpp"
#include "Movable.hpp"
#include "Weapon.hpp"
#include "Bullet.hpp"

class AEntities: public Movable
{
public:
	AEntities(char name, int life, int x, int y, double speed, bool direction);
	AEntities(AEntities const & src);
	virtual ~AEntities() = 0;
	AEntities & operator=(AEntities const & rhs);

	char		getName() const;
	int			getLife() const;
	Weapon		*getWeapon() const;
	void		equip(Weapon *weapon);
	virtual Bullet		*shoot() = 0;
	void		takeDamage(int value);

protected:
	AEntities();

	char		_name;
	int			_life;
	bool		_bdirection;
	Weapon		*_weapon;
};

#endif
