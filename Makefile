# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/31 14:11:32 by ejones            #+#    #+#              #
#    Updated: 2026/08/09 16:59:12 by ejones           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_DIR = MacroLibX
MLX_REPO = https://github.com/seekrs/MacroLibX.git
MLX_LIB = $(MLX_DIR)/libmlx.so

OBJ_DIR := obj
INC_DIR := header

SRC := \
	main.c \
	math/vector_arithmetic.c \
	window/init_window.c \
	window/event_management.c

SRC := $(addprefix src/, $(SRC))

OBJ := $(SRC:src/%.c=$(OBJ_DIR)/%.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INC_DIR) -g

NAME := miniRT

all: $(NAME)

$(NAME): $(OBJ) $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -Imlx -lm -lSDL2 -I$(MLX_DIR)/includes -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_DIR):
	@git clone $(MLX_REPO) $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
