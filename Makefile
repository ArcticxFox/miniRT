MLX_DIR = MacroLibX
MLX_REPO = https://github.com/seekrs/MacroLibX.git
MLX_LIB = $(MLX_DIR)/libmlx.so

LIBFT := src/my_libft/libft.a

OBJ_DIR := obj
INC_DIR := header

SRC := \
	main.c \
	math/vector_arithmetic.c \
	math/quaternions.c \
	window/init_window.c \
	window/event_management.c \
	rendering/intersections/sphere.c \
	rendering/intersections/plane.c \
	rendering/intersections/cylinder.c \
	rendering/intersections/cylinder_utils.c \
	rendering/editor/mode_utils.c \
	rendering/editor/mode_camera.c \
	rendering/editor/mode_move.c \
	rendering/editor/mode_scale.c \
	rendering/editor/mode_rotate.c \
	rendering/ssaa.c \
	parsing/program_setup.c parsing/program_setup_utils.c parsing/parse_line.c \
	parsing/parse_line_utils.c parsing/amb_parse.c \
	parsing/cam_parse.c parsing/light_parse.c \
	parsing/sphere_parse.c parsing/plane_parse.c \
	parsing/cyl_parse.c \
	parsing/number_parsing.c \
	error_handling/errors.c \
	print_all.c \
	rendering/scene.c \
	rendering/scene_utils.c \
	rendering/acceleration/bvh_aabb.c \
	rendering/acceleration/bvh_builds.c \
	rendering/acceleration/bvh_hit_aabb.c \
	rendering/acceleration/bvh_hit.c \
	rendering/acceleration/bvh_range.c \

SRC := $(addprefix src/, $(SRC))

OBJ := $(SRC:src/%.c=$(OBJ_DIR)/%.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror -Wunused-function -I$(INC_DIR) -Isrc/my_libft/headers -g

NAME := miniRT

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -Isrc/my_libft/headers $(MLX_LIB) -Imlx -lm -lSDL2 -I$(MLX_DIR)/includes -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C src/my_libft

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_DIR):
	@git clone $(MLX_REPO) $(MLX_DIR)

clean:
	@$(MAKE) clean -C src/my_libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C src/my_libft

re: fclean all

.PHONY: all clean fclean re
