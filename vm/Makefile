NAME = corewar

LIB = ../libstar/libft.a

INC_DIR = includes/

OP_DIR = op/

SRC =	comparison.c \
		create_op.c \
		get_exec_cycle.c \
		print_arena.c \
		process_execution.c \
		start_game.c \
		turdmonkeys.c \
		vm.c

OP =	*.c

FLAGS = -Wall -Werror -Wextra

RM = rm -Rf

$(NAME):
	cc $(FLAGS) $(SRC) $(OP) -I$(INC_DIR) $(LIB)

all: $(NAME)
