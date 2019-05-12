
NAME	= ft_gkrellm

SRC_D	= srcs/
SRC		= Main.cpp ShellDisplay.cpp GraphDisplay.cpp ModuleHandler.cpp AMonitorDisplay.cpp

MOD_D	= $(SRC_D)modules/
MOD		= HostName.cpp OsInfo.cpp DateTime.cpp CpuInfo.cpp RamInfo.cpp

LIB_D	= libs/

OBJ_D	= objs/
OBJ		= $(addprefix $(OBJ_D), $(SRC:.cpp=.o))
OBJ_2	= $(addprefix $(OBJ_D), $(MOD:.cpp=.o))
LIB_O	= $(addprefix $(LIB_D), $(MOD:.cpp=.so))

INC_D	= includes/
INC		= -I $(INC_D)

CC		= clang++
FLAGS	= -Wall -Werror -Wextra

all: $(OBJ_D) $(NAME) $(OBJ_2) $(LIB_O)

$(OBJ_D):
	@mkdir -p $(OBJ_D)

$(NAME): $(OBJ)
	$(CC) -lncurses -o $@ $^

$(OBJ_D)%.o: $(SRC_D)%.cpp
	$(CC) $(FLAGS) -c -o $@ $< $(INC)

$(OBJ_D)%.o: $(MOD_D)%.cpp
	$(CC) -fPIC -c -o $@ $< $(INC)

$(LIB_D)%.so: $(OBJ_D)%.o
	$(CC) -shared -W1,-soname,$@ -o $@ $^ -lc

clean:
	/bin/rm -r $(OBJ_D)

fclean: clean
	/bin/rm $(NAME)

re: fclean all
