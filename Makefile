NAME		=	eng
CC			=	g++
CFLAGS		=	-Wall -Werror -Wextra# -g3 -fsanitize=address

SRCD		=	srcs/
INCLUDES_D	=	includes/
_INCLUDES	=	eng.h 

_MAIN_FS	=	main.cpp

INCLUDES	=	$(addprefix $(INCLUDES_D),$(_INCLUDES))

MAIN_FS		=	$(addprefix $(SRCD)main/,$(_MAIN_FS))
MAIN_O		=	$(_MAIN_FS:.cpp=.o)

SRCS		=	$(MAIN_FS)
OBJS		=	$(MAIN_O)
OBJD		=	.objs/
OBJB		=	$(addprefix $(OBJD),$(OBJS))

# COLORS
CRED=\033[91m
CGREEN=\033[38;2;0;255;145m
CEND=\033[0m
all: $(NAME)

$(NAME): $(OBJB)
	@printf "\r\033[K$(CGREEN)Creating$(CEND): $(NAME)\n"
	@$(CC) $(CFLAGS) libft/libft.a -L ~/.brew/lib -lglfw -lglew -framework OpenGL $(OBJB) -o $(NAME)
	@echo  "$(NAME): $(CGREEN)done$(CEND)"

$(OBJD)%.o: $(SRCD)main/%.cpp $(INCLUDES) Makefile
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
