#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsergien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/06 15:42:17 by tsergien          #+#    #+#              #
#    Updated: 2018/07/17 14:06:41 by tsergien         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = tsergien.filler

SRC = main.c reader.c distance.c map.c filler.c piece.c inserting.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

HEDER = -I includes/

LIB_DIR = libft/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR)
	@gcc $(OBJ) -o $(NAME) -L $(LIB_DIR) -lft
	@echo "=== ready player one :)==="

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $< $(HEADER)

clean:
	@make -C $(LIB_DIR) clean -silent
	@rm -f $(OBJ)
	@echo "obj files cleaned."

fclean: clean
	@make -C $(LIB_DIR) fclean -silent
	@rm -f $(NAME)
	@echo "player file cleaned."

re: fclean all