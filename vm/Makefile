NAME = corewar

CC = gcc

#FLAGS = -Wall -Werror -Wextra

INC = ./includes

SRC += comparison.c
SRC += create_op.c
SRC += get_exec_cycle.c
SRC += print_arena.c
SRC += process_execution.c
SRC += start_game.c
SRC += vm.c
SRC += op/add.c
SRC += op/aff.c
SRC += op/and.c
SRC += op/fork.c
SRC += op/get_direct_value.c
SRC += op/get_indirect_value.c
SRC += op/get_register_value.c
SRC += op/ld.c
SRC += op/ldi.c
SRC += op/lfork.c
SRC += op/live.c
SRC += op/lld.c
SRC += op/lldi.c
SRC += op/op_controller.c
SRC += op/op.c
SRC += op/or.c
SRC += op/read_parameter.c
SRC += op/st.c
SRC += op/sti.c
SRC += op/sub.c
SRC += op/xor.c
SRC += op/zjmp.c
SRC += get_stats.c
SRC += player_stats.c
SRC += print_game_info.c

LIBFT = ../libstar/libft.a

RM = rm -Rf

$(NAME):
	$(CC) -o$(NAME) $(FLAGS) -I$(INC) $(SRC) $(SRC_MOAR) $(LIBFT)
	@cat ../clap_for_me.txt

all: $(NAME)

clean:
	$(RM) $(NAME)

debug: clean
	$(CC) -g -o$(NAME) $(FLAGS) -I$(INC) $(SRC) $(SRC_MOAR) $(LIBFT)

re: clean all
