NAME		=	eng
CC			=	g++ -std=c++11
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

OSNAME		=	$(shell uname -s)
ifeq ($(OSNAME),Linux)
	COMPILE	=	$(CC) $(CFLAGS) $(OBJB) libft/libft.a -lglfw -lGLEW -lGL -o $(NAME)
endif
ifeq ($(OSNAME),Darwin)
	COMPILE =	$(CC) $(CFLAGS) libft/libft.a -L ~/.brew/lib -lglfw -lglew -framework OpenGL $(OBJB) -o $(NAME)
endif

SRCD		=	srcs/
INCLUDES_D	=	includes/
_INCLUDES	=	eng.h

_MAIN_FS	=	main.cpp
_APP_FS		=	Application.cpp Callbacks.cpp Init.cpp
_WIN_FS		=	Window.cpp

INCLUDES	=	$(addprefix $(INCLUDES_D),$(_INCLUDES))

MAIN_FS		=	$(addprefix $(SRCD)main/,$(_MAIN_FS))
MAIN_O		=	$(_MAIN_FS:.cpp=.o)
APP_FS		=	$(addprefix $(SRCD)Application/,$(_APP_FS))
APP_O		=	$(_APP_FS:.cpp=.o)
WIN_FS		=	$(addprefix $(SRCD)Window/,$(_WIN_FS))
WIN_O		=	$(_WIN_FS:.cpp=.o)

SRCS		=	$(MAIN_FS) $(APP_FS) $(WIN_FS)
OBJS		=	$(MAIN_O) $(APP_O) $(WIN_O)
OBJD		=	.objs/
OBJB		=	$(addprefix $(OBJD),$(OBJS))

UNAME		=	$(uname -s)

# COLORS
CRED=\033[91m
CGREEN=\033[38;2;0;255;145m
CEND=\033[0m
all: $(NAME)

LIBFT = libft/libft.a
$(NAME): $(LIBFT) $(OBJB)
	@printf "\r\033[K$(CGREEN)Creating$(CEND): $(NAME)\n"
	@$(COMPILE)
	@echo  "$(NAME): $(CGREEN)done$(CEND)"

$(LIBFT):
	@make -C libft

$(OBJD)%.o: $(SRCD)main/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

$(OBJD)%.o: $(SRCD)Application/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

$(OBJD)%.o: $(SRCD)Window/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

clean:
	@rm -f $(OBJB)
	@echo "$(CRED)Cleaning$(CEND): $(NAME)"

fclean:
	@make clean
	@rm -f $(NAME)
	@echo "$(CRED)Full cleaning$(CEND): $(NAME)"

re:
	@make fclean
	@make all

#.PHONY: all clean fclean re
