NAME = corewar

CC = gcc

#FLAGS = -Wall -Werror -Wextra

INC = ./includes

SRC + *.c

SRC_MOAR = op/*.c

LIBFT = ../libstar/libft.a

RM = rm -Rf

$(NAME):
	$(CC) -o$(NAME) $(FLAGS) -I$(INC) $(SRC) $(SRC_MOAR) $(LIBFT)

all: $(NAME)

clean:
	$(RM) $(NAME)

debug: clean
	$(CC) -g -o$(NAME) $(FLAGS) -I$(INC) $(SRC) $(SRC_MOAR) $(LIBFT)

re: clean all
