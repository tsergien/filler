#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsergien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/18 19:50:38 by tsergien          #+#    #+#              #
#    Updated: 2018/07/18 19:50:40 by tsergien         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = visualiser

SRC = field.c mlx.c	output.c ../reader.c

OBJ = $(SRC:.c=.o)

WWW = -Wall -Wextra -Werror

FLAGS = -lmlx -framework OpenGl -framework AppKit

HEDER = -I ../includes/

LIB_DIR = ../libft/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR)
	@gcc $(FLAGS) $(OBJ) -I /usr/local/include -L /usr/local/lib/ -L $(LIB_DIR) -lft -o $(NAME)

%.o: %.c
	@gcc $(WWW) -o $@ -c $< $(HEADER)

clean:
	@make -C $(LIB_DIR) clean -silent
	@rm -f $(OBJ)
	@echo "obj files cleaned."

fclean: clean
	@make -C $(LIB_DIR) fclean -silent
	@rm -f $(NAME)
	@echo "visualiser file cleaned."

re: fclean all