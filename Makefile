CORE_NAME = corewar
ASM_NAME = asm
LIBFT = libstar/libft.a
LIB_DIR = libstar/
INC_DIR =	includes/
CORE_DIR = vm/
ASM_DIR = assembler/
RM = rm -f

lib:
	make -C $(LIB_DIR)

all:lib asm corewar 

asm:
	make -C $(ASM_DIR)

corewar:
	make -C $(CORE_DIR)

clean:
	make -C $(CORE_DIR) clean
	make -C $(ASM_DIR) clean
	make -C $(LIB_DIR) clean

fclean:
	make -C $(LIB_DIR) fclean
	$(RM) $(CORE_NAME) $(ASM_NAME)

re: fclean all
