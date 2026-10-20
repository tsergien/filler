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

SRC = src/main.c src/reader.c src/distance.c src/map.c src/filler.c src/piece.c src/inserting.c

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

WWW = -Wall -Wextra -Werror

HEADER = includes/

LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a

all: $(NAME)

# libft is a git submodule: fetch it if the folder is still empty
$(LIB_DIR)Makefile:
	@git submodule update --init $(LIB_DIR)

$(LIBFT): $(LIB_DIR)Makefile FORCE
	@make -C $(LIB_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@gcc $(OBJ) -o $(NAME) -L $(LIB_DIR) -lft
	@echo "=== ready player one :)==="

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR) $(LIB_DIR)Makefile
	@gcc $(WWW) -MMD -MP -I $(HEADER) -I $(LIB_DIR)includes -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@if [ -f $(LIB_DIR)Makefile ]; then make -C $(LIB_DIR) clean -silent; fi
	@rm -rf $(OBJ_DIR)
	@echo "obj files cleaned."

fclean: clean
	@if [ -f $(LIB_DIR)Makefile ]; then make -C $(LIB_DIR) fclean -silent; fi
	@rm -rf $(NAME) viewer/build
	@echo "lib, objs, player, viewer cleaned."

re: fclean all

viewer:
	@cmake -S viewer -B viewer/build > /dev/null
	@cmake --build viewer/build

FORCE:

.PHONY: all clean fclean re viewer FORCE

-include $(DEP)
