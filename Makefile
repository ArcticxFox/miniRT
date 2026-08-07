# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/31 14:11:32 by ejones            #+#    #+#              #
#    Updated: 2026/08/07 14:03:43 by ejones           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_DIR := obj
INC_DIR := header

SRC := \
	main.c \
	math/vector_arithmetic.c

SRC := $(addprefix src/, $(SRC))

OBJ := $(SRC:src/%.c=$(OBJ_DIR)/%.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INC_DIR) -g

NAME := miniRT

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lm -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
