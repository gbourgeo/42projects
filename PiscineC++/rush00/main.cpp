#include "main.hpp"

int				main(void)
{
	Input			input;
	Screen			screen(HEIGHT, WIDTH);
	GameBoard		gameboard;
	PlayerHandler	players;
	EnnemyHandler	ennemies;
	BulletHandler	shots;
	Player			*one;

	/* char name, int life, int x, int y, double speed, shoot direction */
	players.addPlayer(Player('O', 100, 1, (WIDTH - 2) / 2, (HEIGHT - 5), 3.0, true));
	if ((one = players.getPlayer(1)) != nullptr)
		one->equip(new Weapon(0.1, 4.0, '.', 50));

	// ennemies.addEnnemy('U', 50, 6, 10, 2.0, Weapon(1, 80, '*', 50));
	ennemies.addEnnemy('V', 50, 1, 5, 5, 2.0, Weapon(3.0, 8.0, '*', 50));

	gameboard.gameStart();

	while (1) {
		printBorder(screen);
		printScore(screen, gameboard, players);
		ennemies.routine(screen);
		players.routine(screen);
		// Delete Arrived Shots -> Update Shots Position -> Print shots
		shots.moveShots(screen, players, ennemies);
		ennemies.shoot(shots);

		// Store Last Key + Log
		input.setLastKey(wgetch(screen.getWindow()));
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
		if (input.getLastKey() == 27 /* Escape KEY */
			|| one->getRetry() == 0)
			break ;

		wrefresh(screen.getWindow());
	}
	return 0;
}
