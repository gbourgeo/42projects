
NAME = ft_retro

SRC = AEntities.cpp		\
	Bullet.cpp			\
	BulletHandler.cpp	\
	GameBoard.cpp		\
	Ennemy.cpp			\
	EnnemyHandler.cpp	\
	Input.cpp			\
	Logger.cpp			\
	Movable.cpp			\
	Player.cpp			\
	PlayerHandler.cpp	\
	Screen.cpp			\
	Weapon.cpp			\
	main.cpp			\
	Map.cpp				\

CLANG_FLAGS = -Wall -Wextra -Werror -std=c++11

CLANG = clang++

NCURSES = -lncurses

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ)
	$(CLANG) -o $@ $^ $(NCURSES)

$(OBJ_DIR)%.o: %.cpp
	$(CLANG) $(CLANG_FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
