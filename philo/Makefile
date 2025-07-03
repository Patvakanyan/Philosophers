NAME		= philo

SRC			=	src/philo.c src/validate.c src/utils.c src/free_hellper.c src/hellper.c src/sim_attribute.c
OBJ			= $(SRC:.c=.o)

CC			= cc
CFLAGS		= -fsanitize=thread  -g3  -Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJ)

fclean: clean
				$(RM) $(NAME)

re: fclean all

.PHONY: all  clean fclean re
