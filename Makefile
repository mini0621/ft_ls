NAME = ft_ls

CC = gcc 
CFLAGS = -Wall -Werror -Wextra

INCLUDES = ./includes/
LDIR = libftprintf/

LIBFT = libftprintf.a
LIB = -lftprintf


DEPS =

SRC = ft_ls.c inoutput.c list.c prcs_first_dir.c
OBJ = $(SRC:.c=.o)


.PHONY: all fclean clean

RM = rm -f 

all: $(NAME)

$(LIBFT):
	make -C libftprintf/

%.o: %.c
	$(CC) -I $(INCLUDES) -o $@ -c $<  

$(NAME): $(OBJ) $(LIBFT)
	$(CC)  -o $(NAME) $(OBJ) -L $(LDIR) $(LIB) -I$(INCLUDES) -fsanitize=address -g

clean:
	$(RM) $(OBJ)
	make -C libftprintf/ clean

fclean: clean
	$(RM) $(NAME)
	make -C libftprintf/ fclean

re: fclean all
