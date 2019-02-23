NAME = ft_ls

CC = gcc 
CFLAGS = -Wall -Werror -Wextra

INCLUDES = ./includes/
LDIR = libftprintf/

LIBFT = libftprintf.a
LIB = -lftprintf


DEPS =

SRC = ft_ls.c input.c output.c list.c storing.c formatting.c path_string.c prcs_dir.c longfmt.c sort_files.c access_stat.c prcs_files.c lsflags.c
OBJ = $(SRC:.c=.o)

RM = rm -f 

.PHONY: all fclean clean

	
all: $(NAME)

$(LIBFT):
	make -C libftprintf/

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJ)
	make -C libftprintf/
	$(CC) -o $@ $(OBJ) -L $(LDIR) $(LIB)

clean:
	$(RM) $(OBJ)
	make -C libftprintf/ clean

fclean: clean
	$(RM) $(NAME)
	make -C libftprintf/ fclean

re: fclean all
