NAME = ft_retro

SRC = AEntities.cpp	\
	Bullet.cpp		\
	GameBoard.cpp	\
	Ennemy.cpp		\
	Input.cpp		\
	Logger.cpp		\
	Movable.cpp		\
	Player.cpp		\
	Screen.cpp		\
	Weapon.cpp		\
	main.cpp		\
	map.cpp

CLANG_FLAGS = -Wall -Wextra -Werror

CLANG = clang++

NCURSES = -lncurses

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ)
	$(CLANG) -fsanitize=address -o $@ $^ $(NCURSES)

$(OBJ_DIR)%.o: %.cpp
	$(CLANG) $(CLANG_FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all re clean fclean
