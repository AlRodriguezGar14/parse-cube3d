NAME	= parse_cube
CC		= cc
CFLAGS	= -Wall -Wextra -Werror # -fsanitize=address -g3

FILES	=	srcs/main \


CFILES	= $(addsuffix .c, $(FILES))
OBJS	= $(addsuffix .o, $(FILES))
HEADERS	= includes/
LIBFT_DIR	= srcs/libft

all: $(NAME)

.c.o: $(CFILES)
	$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) -o $@ $^ -L $(LIBFT_DIR) -lft $(LDFLAGS)

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
