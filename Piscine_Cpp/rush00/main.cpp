#include "main.hpp"

void			newGame(PlayerHandler & players, EnnemyHandler & ennemies, BulletHandler & bullets)
{
	Player		*one;

	players.reset();
	players.addPlayer(Player('O', 100, 1, (WIDTH - 2) / 2, (HEIGHT - 5), 3.0, true));
	/* char name, int life, int x, int y, double speed, shoot direction */
	if ((one = players.getPlayer(1)) != nullptr)
		one->equip(new Weapon(0.1, 4.0, '.', 50));

	ennemies.reset();
	ennemies.addEnnemy('V', 50, 1, 5, 5, 2.0, Weapon(3.0, 8.0, '*', 50));
	ennemies.addEnnemy('U', 50, 1, 4, 10, 2.0, Weapon(2.0, 6.0, '*', 50));

	bullets.reset();
}

int				retryGame(Screen & screen, GameBoard & gameboard,
PlayerHandler & players, EnnemyHandler & ennemies, BulletHandler & bullets)
{
	int		ret;

	printBorder(screen);
	printScore(screen, gameboard, players);
	mvwprintw(screen.getWindow(), HEIGHT / 2, WIDTH / 2 - 3, "RETRY");
	mvwprintw(screen.getWindow(), HEIGHT / 2 + 1, WIDTH / 2 - 3, "y / n");
	while (1)
	{
		ret = wgetch(screen.getWindow());
		if (ret == ERR)
			continue ;
		if (ret != 'y')
			return 0;
		newGame(players, ennemies, bullets);
		return 1;
	}
}

int				main(void)
{
	Input			input;
	Screen			screen(HEIGHT, WIDTH);
	GameBoard		gameboard;
	PlayerHandler	players;
	EnnemyHandler	ennemies;
	BulletHandler	shots;
	Player			*one;

	newGame(players, ennemies, shots);
	gameboard.gameStart();
	while (1)
	{
		printBorder(screen);
		printScore(screen, gameboard, players);
		shots.moveShots(screen, players, ennemies);
		ennemies.routine(screen);
		players.routine(screen);
		// Delete Arrived Shots -> Update Shots Position -> Print shots
		ennemies.shoot(shots);

		// Store Last Key
		input.setLastKey(wgetch(screen.getWindow()));
		one = players.getPlayer(1);
		if (one->getLife() > 0)
		{
			if (input.getLastKey() == KEY_LEFT && one->getX() > 2) {
				one->move(one->getX() - 1, one->getY());
			} else if (input.getLastKey() == KEY_RIGHT && one->getX() < WIDTH - 2) {
				one->move(one->getX() + 1, one->getY());
			} else if (input.getLastKey() == KEY_UP && one->getY() > 3) {
				one->move(one->getX(), one->getY() - 1);
			} else if (input.getLastKey() == KEY_DOWN && one->getY() < HEIGHT - 2) {
				one->move(one->getX(), one->getY() + 1);
			} else if (input.getLastKey() == ' ') {
				shots.addShot(one->shoot());
			}
		}
		if (input.getLastKey() == 27) /* Escape KEY */
			break ;
		if (one->getRetry() == 0
			&& !retryGame(screen, gameboard, players, ennemies, shots))
			break ;

		wrefresh(screen.getWindow());
	}
	return 0;
}
