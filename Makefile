# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread

# Project name
NAME    = philo

# Sources & Objects
SRC     = $(wildcard *.c)
OBJ     = $(SRC:.c=.o)

# Default rule
all: $(NAME)

# Linking step
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	rm -f $(OBJ)

# Remove objects + binary
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re

