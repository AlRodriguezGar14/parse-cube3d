NAME	= parse_cube
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g3

FILES	=	srcs/main \
			srcs/validators/validate_file \
			srcs/validators/validate_map \
			srcs/parser/parsers \
			srcs/parser/parsing_utils \
			srcs/utils \
			srcs/key_hooks_terminal/movements \
			srcs/key_hooks_terminal/key_hook_terminal \


CFILES	= $(addsuffix .c, $(FILES))
OBJS	= $(addsuffix .o, $(FILES))
HEADERS	= includes/
LIBFT_DIR	= srcs/libft
MINILIBX_DIR = mlx/
MINILIBX = $(MINILIBX_DIR)libmlx.a

all: $(NAME) $(MINILIBX)

.c.o: $(CFILES)
	$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MINILIBX_DIR)
		$(CC) $(CFLAGS) -o $@ $^  -L $(MINILIBX_DIR) -lmlx -L $(LIBFT_DIR) -lft $(LDFLAGS) -framework OpenGL -framework AppKit

fsanitize:
	$(eval CFLAGS +=-fsanitize=address -g3)

sanitize: fsanitize all

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf *.dSYM
	rm -rf srcs/libft/libft.a

re: fclean all

.PHONY: all clean fclean re
