NAME		=	libdn.a
CC			=	g++ -std=c++14
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

GET_PACKAGE	=	`pkg-config --static --libs glew glfw3 openal`

MAIN_FILE	= main.cpp
OUT			= a.out

OSNAME		= $(shell uname -s)
ifeq ($(OSNAME),Linux)
	COMPILE	= $(CC) $(MAIN_FILE) $(NAME) $(GET_PACKAGE) -lsndfile -I includes/ -I libft/includes/ -o $(OUT)# -g3 -fsanitize=address
endif
ifeq ($(OSNAME),Darwin)
	COMPILE = $(CC) $(MAIN_FILE) $(NAME) $(GET_PACKAGE) -framework OpenGL -I includes/ -I libft/includes/ -o $(OUT)# -g3 -fsanitize=address
endif

SRCD		= srcs/
INCLUDES_D	= includes/
_INCLUDES	= eng.hpp Window.hpp Application.hpp Color.hpp Funcs.hpp Event.hpp Object.hpp \
			  Shader.hpp Vertex.hpp Model.hpp Component.hpp Transform.hpp MeshRenderer.hpp \
			  Prototype.hpp Camera.hpp stb_image.h Codes.hpp ApplicationDependent.hpp \
			  Audio.hpp AudioSource.hpp AudioListener.hpp utils.hpp Scene.hpp ModelInstance.hpp

_MAIN_FS	=
_APP_FS		= application.cpp callbacks.cpp init.cpp \
			  manage_window.cpp manage_dependents.cpp applicationDependent.cpp
_WIN_FS		= window.cpp getset.cpp setcallbacks.cpp color.cpp
_SHDR_FS	= shader.cpp defaultShader.cpp
_MESH_FS	= prototype.cpp model.cpp models.cpp
_MATH_FS	= smoothDamp.cpp random.cpp
_OBJ_FS		= object.cpp component.cpp transform.cpp meshrenderer.cpp camera.cpp
_TXTR_FS	= texture.cpp
_AUDIO_FS	= audio.cpp audioSource.cpp audioListener.cpp
_UTILS_FS	= utils.cpp
_SCENE_FS	= scene.cpp modelInstance.cpp

INCLUDES	= $(addprefix $(INCLUDES_D),$(_INCLUDES))

MAIN_FS		= $(addprefix $(SRCD)main/,$(_MAIN_FS))
MAIN_O		= $(_MAIN_FS:.cpp=.o)
APP_FS		= $(addprefix $(SRCD)Application/,$(_APP_FS))
APP_O		= $(_APP_FS:.cpp=.o)
WIN_FS		= $(addprefix $(SRCD)Window/,$(_WIN_FS))
WIN_O		= $(_WIN_FS:.cpp=.o)
SHDR_FS		= $(addprefix $(SRCD)Shader/,$(_SHDR_FS))
SHDR_O		= $(_SHDR_FS:.cpp=.o)
MESH_FS		= $(addprefix $(SRCD)Model/,$(_MESH_FS))
MESH_O		= $(_MESH_FS:.cpp=.o)
MATH_FS		= $(addprefix $(SRCD)Math/,$(_MATH_FS))
MATH_O		= $(_MATH_FS:.cpp=.o)
OBJ_FS		= $(addprefix $(SRCD)Object/,$(_OBJ_FS))
OBJ_O		= $(_OBJ_FS:.cpp=.o)
TXTR_FS		= $(addprefix $(SRCD)Texture/,$(_TXTR_FS))
TXTR_O		= $(_TXTR_FS:.cpp=.o)
AUDIO_FS	= $(addprefix $(SRCD)Audio/,$(_AUDIO_FS))
AUDIO_O		= $(_AUDIO_FS:.cpp=.o)
UTILS_FS	= $(addprefix $(SRCD)utils/,$(_UTILS_FS))
UTILS_O		= $(_UTILS_FS:.cpp=.o)
SCENE_FS	= $(addprefix $(SRCD)Scene/,$(_SCENE_FS))
SCENE_O		= $(_SCENE_FS:.cpp=.o)

SRCS		= $(MAIN_FS) $(APP_FS) $(WIN_FS) $(SHDR_FS) $(MESH_FS) $(MATH_FS) \
			  $(OBJ_FS) $(TXTR_FS) $(AUDIO_FS) $(UTILS_FS) $(SCENE_FS)
OBJS		= $(MAIN_O) $(APP_O) $(WIN_O) $(SHDR_O) $(MESH_O) $(MATH_O) \
			  $(OBJ_O) $(TXTR_O) $(AUDIO_O) $(UTILS_O) $(SCENE_O)
OBJD		= .objs/
OBJB		= $(addprefix $(OBJD),$(OBJS))

# COLORS
CRED=\033[91m
CGREEN=\033[38;2;0;255;145m
CEND=\033[0m
all: $(NAME)

$(NAME): $(OBJB)
	@printf "\r\033[K$(CGREEN)Creating$(CEND): $(NAME)\n"
	@ar rc $(NAME) $(OBJB)
	@ranlib $(NAME)
	@echo  "$(NAME): $(CGREEN)done$(CEND)"

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

$(OBJD)%.o: $(SRCD)Shader/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

$(OBJD)%.o: $(SRCD)Model/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

$(OBJD)%.o: $(SRCD)Math/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

$(OBJD)%.o: $(SRCD)Object/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

$(OBJD)%.o: $(SRCD)Texture/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

$(OBJD)%.o: $(SRCD)Audio/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

$(OBJD)%.o: $(SRCD)utils/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

$(OBJD)%.o: $(SRCD)Scene/%.cpp $(INCLUDES) Makefile
	@printf "\r\033[K$(CGREEN)Compiling$(CEND): $<"
	@mkdir -p $(OBJD)
	@$(CC) $(CLFAGS) -o $@ -c $< -I$(INCLUDES_D) -I libft/includes

clean:
	@echo "$(CRED)Cleaning$(CEND): $(NAME)"
	@rm -rf $(OBJD)
	@rm -f $(NAME)

fclean:
	@make clean

re:
	@make clean
	@make all

main:
	make $(NAME)
	$(COMPILE)

#.PHONY: all clean fclean re
