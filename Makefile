NAME := MiniRT
CC := cc
CFLAGS := -Wall -Werror -Wextra -g
LIBFT := src/my_libft/libft.a


SRC_DIR := src

SRC := main.c parsing/program_setup.c parsing/parse_line.c parsing/parse_line_utils.c parsing/amb_parse.c parsing/cam_parse.c

SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRC))

OBJ_DIR := obj
OBJ := $(SRC:.c=.o)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT)

$(LIBFT):
	$(MAKE) bonus -C src/my_libft


./$(OBJ_DIR)/%.o : ./$(SRC_DIR)/%.c
	mkdir -p ./$(dir $@)
	$(CC) $(CFLAGS) -Iincludes -Isrc/my_libft/headers -c $< -o $@

clean:
	$(MAKE) clean -C src/my_libft
	rm -rf ./$(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C src/my_libft

re: fclean all

.PHONY: all clean fclean re


