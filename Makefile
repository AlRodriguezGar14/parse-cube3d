#Comandos
DEL			=	rm -f
CC			=	gcc -g3
CCFLAGS		=	-Wall -Wextra -Werror -g3 #-fsanitize=address -g3
#MLX			=	-framework OpenGL -framework AppKit
MLX			=	-lXext -lX11 -lm -lbsd 
# -g3 -fsanitize=address

#Nombre ejecutable
NAME		=	cub3d

#Ficheros
SRC_FILES	= main \
			parser/parsers \
			parser/parsing_utils \
			utils \
			free_content \
			key_hooks_terminal/movements \
			key_hooks_terminal/key_hook_terminal \
			validators/validate_file \
			validators/validate_map \
			game/game \
			game/game_2 \
			game/game_3 \
			game/get_inter \
			game/keys \
			game/textures \
			game/minimap \
	

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

LIBFT		=	srcs/libft
MINILIBX	= 	mlx

#Librerias 
LIBS		= $(MINILIBX)/libmlx.a $(MLX) $(LIBFT)/libft.a 

#Directorios
SRC_DIR = srcs/
OBJ_DIR = objs/

# REGLAS # 
all:	minilibx libft $(NAME)

#Compilar 
$(NAME):$(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME)
		@echo "$(GREEN)CUB3D HAS BEEN COMPILED!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/validators
	@mkdir -p $(OBJ_DIR)/key_hooks_terminal
	@mkdir -p $(OBJ_DIR)/game
	
	@echo "$(YELLOW)Compiling: $<$(NC)"
	@$(CC) $(CFLAGS) -o $@ -c $< 
	@echo "$(YELLOW)Compiled!$(NC)"
	
# $@ : The file name of the target of the rule. If the target is an archive member, then ‘$@’ is the name of the archive file.
# $< : The name of the first prerequisite.

#compilar librerias individuales
libft:
	@echo "$(YELLOW)COMPILING LIBFT...$(NC)"
	@$(MAKE) -C ./$(LIBFT)
	@echo "$(GREEN)LIBFT HAS BEEN COMPILED$(NC)"

minilibx:
	@echo "$(YELLOW)COMPILING MINILIBX...$(NC)"
	@$(MAKE) -C ./$(MINILIBX)
	@echo "$(GREEN)MINILIBX HAS BEEN COMPILED$(NC)"

# Eliminar tmp mlx
fclean_mlx:
	@make fclean -C ./$(MINILIBX)
	@echo "$(RED)MINILIBX FULL CLEANED!$(NC)"


# Eliminar tmp libft
fclean_libft:
	@make fclean -C ./$(LIBFT)
	@echo "$(RED)LIBFT FULL CLEANED!$(NC)"

# Eliminar temporales
clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(RED)OBJS AND DIRECTORY CLEANED!$(NC)"


# Eliminar temporales y ejecutable fclean_mlx
fclean: clean  fclean_libft
	@$(RM) $(NAME)
	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"


re: fclean all