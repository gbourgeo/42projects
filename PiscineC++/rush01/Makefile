
NAME	= ft_gkrellm

SRC_D	= srcs/
SRC		= Main.cpp			\
		ShellDisplay.cpp	\
		GraphDisplay.cpp	\
		ModuleHandler.cpp	\
		AMonitorDisplay.cpp	\

MOD_D	= $(SRC_D)modules/
MOD		= HostName.cpp		\
		OsInfo.cpp			\
		DateTime.cpp		\
		CpuInfo.cpp			\
		RamInfo.cpp			\

LIB_D	= libs/

OBJ_D	= objs/
OBJ		= $(addprefix $(OBJ_D), $(SRC:.cpp=.o))
OBJ_D2	= $(OBJ_D)modules/
OBJ_2	= $(addprefix $(OBJ_D2), $(MOD:.cpp=.o))
LIB_O	= $(addprefix $(LIB_D), $(MOD:.cpp=.so))

INC_D	= includes/
INC		= -I $(INC_D) -I $(INC_D)modules

CC		= clang++
CC11	= -std=c++11
FLAGS	= -Wall -Werror -Wextra

all: $(OBJ_D) $(OBJ_D2) $(LIB_D) $(OBJ_2) $(LIB_O) $(NAME)

$(OBJ_D):
	@mkdir -p $@

$(OBJ_D2):
	@mkdir -p $@

$(LIB_D):
	mkdir -p $@

$(NAME): $(OBJ)
	$(CC) -o $@ $^ -lncurses -ldl

$(OBJ_D)%.o: $(SRC_D)%.cpp
	$(CC) $(CC11) $(FLAGS) -c -o $@ $< $(INC)

$(OBJ_D2)%.o: $(MOD_D)%.cpp
	$(CC) $(CC11) -fPIC -c -o $@ $< $(INC)

$(LIB_D)%.so: $(OBJ_D2)%.o
	$(CC) $(CC11) -shared -W1,-soname,$@ -o $@ $^ -lc

clean:
	/bin/rm -rf $(OBJ_D)

fclean: clean
	/bin/rm -rf $(LIB_D)
	/bin/rm -f $(NAME)

re: fclean all
