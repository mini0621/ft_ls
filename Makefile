# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/23 02:37:51 by mnishimo          #+#    #+#              #
#    Updated: 2019/02/26 20:28:27 by mnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc 
CFLAGS = -Wall -Werror -Wextra

INCLUDES = ./includes/
LDIR = libftprintf/

LIBFT = libftprintf.a
LIB = -lftprintf

DEPS = includes/lscolors.h includes/ft_ls.h 
SRC = ft_ls.c input.c output.c list.c storing.c formatting.c path_string.c prcs_dir.c longfmt.c sort_files.c access_stat.c prcs_files.c lsflags.c lscolors.c
OBJ = $(SRC:.c=.o)

RM = rm -f 

.PHONY: all fclean clean
	
all: $(NAME)

$(LIBFT):
	make -C libftprintf/

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJ) $(DEPS)
	make -C libftprintf/
	$(CC) -o $@ $(OBJ) -L $(LDIR) $(LIB)

clean:
	$(RM) $(OBJ)
	make -C libftprintf/ clean

fclean: clean
	$(RM) $(NAME)
	make -C libftprintf/ fclean

re: fclean all
