NAME = libft.a
FLAGS = -Wall -Werror -Wextra -I. -I/ftprintf -c
CC = gcc
OBJSRC = $(patsubst %, %.o, $(SRC))



# GENERAL LIBFT FUNCTIONS
SRC += ft_strlen
SRC += ft_memalloc
SRC += ft_strcpy
SRC += ft_bzero
SRC += ft_isalpha
SRC += ft_isdigit
SRC += ft_memdel
SRC += ft_memset
SRC += ft_strncpy
SRC += ft_strcat
SRC += ft_strnew
SRC += ft_strsplit
SRC += ft_strsub
SRC += ft_strcmp
SRC += ft_memcpy
SRC += ft_memmove
SRC += ft_queue
SRC += ft_queue_util
SRC += ft_dblistnew
SRC += ft_mergesort
SRC += ft_strdup
SRC += ft_strchr
SRC += ft_numlen
SRC += ft_strnstr
SRC += ft_strchr
SRC += ft_nlookup
SRC += ft_atoi
SRC += ft_lstadd
SRC += ft_isalnum
SRC += ft_strnequ
SRC += ft_strncmp
SRC += pqueue


# FTPRINTF
SRC += ftprintf/conversion_diou
SRC += ftprintf/dispatcher
SRC += ftprintf/printflags
SRC += ftprintf/conversion_sc
SRC += ftprintf/storeflags
SRC += ftprintf/conversion_xp
SRC += ftprintf/misc
SRC += ftprintf/ulitobase

all: $(NAME)

$(NAME): $(OBJSRC)
	@ echo "Building static library..."
	@ ar -rcs $(NAME) $(OBJSRC)

%.o: %.c
	@ echo "Compiling $<..."
	@ $(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@ /bin/rm -f $(OBJSRC)
	@ echo "Cleaning folders of object files..."

fclean: clean
	@ /bin/rm -f $(NAME)
	@ echo "Removing library file and binary..."

re: fclean all
	@ echo "Program Remade"