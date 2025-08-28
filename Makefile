CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread

NAME    = philo

SRC     = forks.c forks_plus.c initialization.c initialization_plus.c \
          main.c monitor.c tools.c toolds1.c time_utils.c
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
