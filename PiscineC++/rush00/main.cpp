#include "main.hpp"

static void		printScore(WINDOW *window, GameBoard & gameboard)
{
	double	ret;
	size_t	min;
	int		sec;

	mvwprintw(window, 1, 1, "SCORE");
	mvwprintw(window, 1, (WIDTH + 3) / 2, "TIME");
	mvwprintw(window, 1, (WIDTH - 6), "LIVES");

	mvwprintw(window, 2, 1, "%d", gameboard.getScore());
	ret = difftime(time(0), gameboard.getTiming());
	min = (size_t)ret / 60;
	sec = (int)ret % 60;
	mvwprintw(window, 2, (WIDTH + 3) / 2, "%ld:%02d", min, sec);
	mvwprintw(window, 2, (WIDTH - 2), "%d", gameboard.getLives());
}


t_shot		*removeShot(Bullet *b, t_shot *lst) {
	t_shot		*tmp;
	t_shot		*prev;

	tmp = lst;
	prev = NULL;
	
	Logger	l("sigv");
	while (tmp) {
		if (tmp->shot == b)
			break;
		tmp = tmp->next;
	}
	if (tmp) {
		if (tmp->prev) {
			tmp->prev->next = tmp->next;
		} else {
			lst = tmp->next;
		}
		if (tmp->next) {
			tmp->next->prev = tmp->prev;
		}
		delete tmp->shot;
		delete tmp;
	}
	return lst;
}

t_shot			*deleteShots(t_shot *shots) {
	t_shot 		*tmp;
	t_shot 		*tmp2;

	tmp = shots;
	while (tmp && tmp->shot) {
		if (tmp->shot->isArrived()) {
			tmp2 = tmp->next;
			shots = removeShot(tmp->shot, shots);
			tmp = tmp2;
		} else {
			tmp = tmp->next;
		}
	}
	return shots;
}

t_shot		*shotsHandler(WINDOW *window, t_shot *shots)
{
	shots = deleteShots(shots);

	t_shot		*tmp;

	tmp = shots;
	while (tmp && tmp->shot) {
		tmp->shot->updatePosition();
		mvwprintw(window, tmp->shot->getY(), tmp->shot->getX(), "%c", tmp->shot->getName());	
		tmp = tmp->next;
	}
	return shots;
}

static t_ennemy	*createEnnemies(char name, int life, int nb, int y, double speed)
{
	t_ennemy	*E = nullptr;
	int			x, z;

	z = (WIDTH - 2) / nb;
	x = 0;
	for (int i = 0; i < nb; i++) {
		x += z;
		t_ennemy *F = new t_ennemy;
		F->ennemy = new Ennemy(name, life, x, y, speed, false);
		F->ennemy->equip(new Weapon(1, 40, '*', 50));
		F->next = E;
		E = F;
	}
	return E;	
}

static void			addShot(Bullet *b, t_shot *lst) {

	if (!(lst->shot)) {
		lst->shot = b;
		lst->next = NULL;
	} else {

		t_shot		*tmp;
		t_shot		*n = new t_shot;

		tmp = lst;
		n->next = NULL;
		n->prev = NULL;
		n->shot = b;

		while (tmp->next) 
			tmp = tmp->next;

		tmp->next = n;
		n->prev = tmp;
	}
}

static void		printEnnemies(WINDOW *w, t_ennemy *ptr)
{
	while (ptr)
	{
		if (ptr->ennemy)
			mvwprintw(w, ptr->ennemy->getY(), ptr->ennemy->getX(), "%c", ptr->ennemy->getName());
		ptr = ptr->next;
	}
}

int				main(void) {
    Input		input("ft_retro.log");
    Screen		screen(HEIGHT, WIDTH);
	GameBoard	gameboard(0, 3); /* (SCORE, LIVES) */
    bool		loop = true;
	/* char name, int life, int x, int y, double speed */
	Player		player1('O', 100, (WIDTH - 2) / 2, (HEIGHT - 5), 1.0, true);
	/* shootRate, bulletSpeed, bulletName, bulletDamage */
	Weapon		weapon1(10, 4.0, '.', 50);
	t_ennemy	*firstLine;
	t_ennemy	*secondLine;
	t_shot		*shots = new t_shot;
	shots->next = NULL;
	shots->shot = NULL;
	shots->prev = NULL;
    WINDOW		*window = screen.getWindow();

	player1.equip(&weapon1);
	firstLine = createEnnemies('U', 50, 6, 10, 5.0);
	secondLine = createEnnemies('V', 50, 5, 5, 5.0);
    while (loop) {
        wclear(window);
        box(window, '|', '-');
		printScore(window, gameboard);
		printMap(window);
		mvwprintw(window, player1.getY(), player1.getX(), "%c", player1.getName());
		printEnnemies(window, firstLine);
		printEnnemies(window, secondLine);
		// Delete Arrived Shots -> Update Shots Position -> Print shots
		shots = shotsHandler(window, shots);

		for (t_ennemy *ptr=firstLine; ptr; ptr=ptr->next) {
			if (ptr->ennemy->getWeapon()->canShoot()) {
				addShot(ptr->ennemy->shoot(), shots);
			}
		}

        // Store Last Key + Log
        input.setLastKey(wgetch(window));
        if (input.getLastKey() == KEY_LEFT && player1.getX() > 2) {
			player1.move(player1.getX() - 1, player1.getY());
        } else if (input.getLastKey() == KEY_RIGHT && player1.getX() < WIDTH - 2) {
			player1.move(player1.getX() + 1, player1.getY());
        } else if (input.getLastKey() == ' ') {
			addShot(player1.shoot(), shots);
		}
		
        wrefresh(window);

        input.log(FILE, "max width == " , screen.getWidth());
        input.log(FILE, "max height == ", screen.getHeight());
    }
	// for (size_t i = 0; i < shots.size(); i++) {
	// 	delete shots[i];
	// }
	for (t_ennemy *ptr = firstLine; ptr; ptr = ptr->next) {
		if (ptr->ennemy)
			delete ptr->ennemy;
		delete ptr;
	}
    return 0;
}
