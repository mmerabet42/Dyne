NAME		=	libeng.a
CC			=	g++ -std=c++11
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

MAIN_FILE	=	main.cpp
OUT			=	a.out

OSNAME		=	$(shell uname -s)
ifeq ($(OSNAME),Linux)
	COMPILE	=	$(CC) $(MAIN_FILE) $(NAME) libft/libft.a -lglfw -lGLEW -lGL -I includes/ -I libft/includes/ -o $(OUT)
endif
ifeq ($(OSNAME),Darwin)
	COMPILE =	$(CC) $(MAIN_FILE) $(NAME) libft/libft.a -L ~/.brew/lib -lglfw -lglew -framework OpenGL -I includes/ -I libft/includes/ -o $(OUT)
endif

SRCD		=	srcs/
INCLUDES_D	=	includes/
_INCLUDES	=	eng.h Window.h Application.h Color.h Funcs.h

_MAIN_FS	=
_APP_FS		=	application.cpp callbacks.cpp init.cpp
_WIN_FS		=	window.cpp getset.cpp setcallbacks.cpp color.cpp

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
	@ar rc $(NAME) $(OBJB)
	@ranlib $(NAME)
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
	@echo "$(CRED)Cleaning$(CEND): $(NAME)"
	@rm -f $(OBJB)
	@rm -f $(NAME)

fclean:
	@echo "$(CRED)Cleaning$(CEND): $(NAME)"
	@make fclean -C libft
	@rm -f $(OBJB)
	@rm -f $(NAME)

re:
	@make fclean
	@make all

main:
	make $(NAME)
	$(COMPILE)

#.PHONY: all clean fclean re
