NAME = philo

CFLAGS = -g -Wall -Werror -Wextra

CC = cc

OBJ_DIR = obj/

SRC_DIR = src/

HEADERS = := -I ./include

SRC := main.c parsing.c utils.c init.c get_set.c sim.c oversee.c\

OBJ = $(SRC:.c=.o)

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re