#ifndef MAIN_HPP
 #define MAIN_HPP

#include <curses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <sys/time.h>

#include "Logger.hpp"
#include "Input.hpp"
#include "Screen.hpp"
#include "GameBoard.hpp"
#include "AEntities.hpp"
#include "Player.hpp"
#include "Ennemy.hpp"
#include "Weapon.hpp"
#include "Movable.hpp"
#include "Bullet.hpp"

#define HEIGHT 50
#define WIDTH 80
#define MOVE_RATIO 0.1f

typedef struct		s_ennemy
{
	Ennemy			*ennemy;
	struct s_ennemy *next;
}					t_ennemy;

typedef struct		s_shot
{
	Bullet			*shot;
	struct s_shot	*next;
	struct s_shot	*prev;
}					t_shot;

int main(void);
void printMap(WINDOW *w);

#endif
