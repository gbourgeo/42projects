
NAME	= ft_gkrellm

SRC_DIR	= srcs/
SRC		= Main.cpp			\

DIS_DIR	= $(SRC_DIR)displays/
DIS		= ShellDisplay.cpp	\
		ModuleHandler.cpp	\
		AMonitorDisplay.cpp	\
#		GraphDisplay.cpp	\

MOD_DIR	= $(SRC_DIR)modules/
MOD		= HostName.cpp		\
		OsInfo.cpp			\
		DateTime.cpp		\
		CpuInfo.cpp			\
		RamInfo.cpp			\
		AMonitorModule.cpp	\

OBJ_DIR		= objs/
OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
OBJ_DIS_DIR	= $(OBJ_DIR)displays/
OBJ			+= $(addprefix $(OBJ_DIS_DIR), $(DIS:.cpp=.o))
OBJ_MOD_DIR	= $(OBJ_DIR)modules/
OBJ			+= $(addprefix $(OBJ_MOD_DIR), $(MOD:.cpp=.o))

# Create specific directory for the modules .so library
LIB_DIR		= libs/
OBJ_LIB		= $(addprefix $(LIB_DIR), $(MOD:.cpp=.so))

INC_DIR		= includes/
INCLUDES	= -I $(INC_DIR) -I $(INC_DIR)displays -I $(INC_DIR)displays/Qt -I $(INC_DIR)modules

CC		= clang++
CC11	= -std=c++11
FLAGS	= -Wall -Werror -Wextra

all: $(OBJ_DIR) $(OBJ_DIS_DIR) $(OBJ_MOD_DIR) $(LIB_DIR) $(OBJ) $(OBJ_LIB) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIS_DIR): $(OBJ_DIR)
	@mkdir -p $@

$(OBJ_MOD_DIR): $(OBJ_DIR)
	@mkdir -p $@

$(LIB_DIR):
	mkdir -p $@

$(NAME): $(OBJ)
	$(CC) -o $@ $^ -lncurses -ldl

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(CC11) $(FLAGS) -c -o $@ $< $(INCLUDES)

$(OBJ_DIS_DIR)%.o: $(DIS_DIR)%.cpp
	$(CC) $(CC11) $(FLAGS) -c -o $@ $< $(INCLUDES)

$(OBJ_MOD_DIR)%.o: $(MOD_DIR)%.cpp
	$(CC) $(CC11) -fPIC -c -o $@ $< $(INCLUDES)

$(LIB_D)%.so: $(OBJ_LIB)%.o
	$(CC) $(CC11) -shared -W1,-soname,$@ -o $@ $^ -lc

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -rf $(LIB_DIR)
	/bin/rm -f $(NAME)

re: fclean all
