DEL			=	rm -f
CC			=	cc -g3  -O2 -Wuninitialized
CCFLAGS		=	-Wall -Wextra -Werror # -g3 -fsanitize=address
#MLX			=	-framework OpenGL -framework AppKit
 MLX			=	-lXext -lX11 -lm -lbsd 



NAME		=	cub3d


SRC_FILES	= main \
			parser/parsers \
			parser/parsing_utils \
			utils \
			free_content \
			validators/validate_file \
			validators/validate_map \
			validators/setter \
			game/game \
			game/img_getters \
			game/keys \
			game/textures \
			game/minimap \
			game/init_ray \
			game/wall \
			game/move \
			game/move_aux \
			game/print_terminal \
			game/mouse
			
	

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

LIBFT		=	srcs/libft
MINILIBX	= 	mlx


LIBS		= $(MINILIBX)/libmlx.a $(MLX) $(LIBFT)/libft.a 


SRC_DIR = srcs/
OBJ_DIR = objs/


all:	minilibx libft $(NAME)

 
$(NAME):$(OBJ)
		$(CC)  $(OBJ) $(LIBS) -o $(NAME)
		@echo "$(GREEN)CUB3D HAS BEEN COMPILED!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/validators
	@mkdir -p $(OBJ_DIR)/game
	
	@echo "$(YELLOW)Compiling: $<$(NC)"
	@$(CC) $(CCFLAGS) -o $@ -c $< 
	@echo "$(YELLOW)Compiled!$(NC)"
	
# $@ : The file name of the target of the rule. If the target is an archive member, then ‘$@’ is the name of the archive file.
# $< : The name of the first prerequisite.

libft:
	@echo "$(YELLOW)COMPILING LIBFT...$(NC)"
	@$(MAKE) -C ./$(LIBFT)
	@echo "$(GREEN)LIBFT HAS BEEN COMPILED$(NC)"

minilibx:
	@echo "$(YELLOW)COMPILING MINILIBX...$(NC)"
	@$(MAKE) -C ./$(MINILIBX)
	@echo "$(GREEN)MINILIBX HAS BEEN COMPILED$(NC)"

fclean_mlx:
	@make fclean -C ./$(MINILIBX)
	@echo "$(RED)MINILIBX FULL CLEANED!$(NC)"



fclean_libft:
	@make fclean -C ./$(LIBFT)
	@echo "$(RED)LIBFT FULL CLEANED!$(NC)"


clean:
	@$(RM) -rf $(OBJ_DIR)
	@$(RM) -rf $(OBJ_DIR)/parser
	@$(RM) -rf $(OBJ_DIR)/validators
	@$(RM) -rf $(OBJ_DIR)/key_hooks_terminal
	@$(RM) -rf $(OBJ_DIR)/game
	@echo "$(RED)OBJS AND DIRECTORY CLEANED!$(NC)"


fclean: clean  fclean_libft
	@$(RM) $(NAME)
	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"


re: fclean all
