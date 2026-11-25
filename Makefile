MLX_DIR = MacroLibX
MLX_REPO = https://github.com/seekrs/MacroLibX.git
MLX_LIB = $(MLX_DIR)/libmlx.so

LIBFT := src/my_libft/libft.a

OBJ_DIR := obj
INC_DIR := header

SRC := \
	main.c \
	objects.c \
	camera.c \
	math/vector_arithmetic.c \
	math/quaternions.c \
	window/init_window.c \
	window/event_management.c \
	rendering/intersections/sphere.c \
	rendering/intersections/plane.c \
	rendering/intersections/cylinder.c \
	rendering/editor/mode_utils.c \
	rendering/editor/mode_camera.c \
	rendering/editor/mode_move.c \
	rendering/editor/mode_scale.c \
	rendering/editor/mode_rotate.c \
	rendering/supersampling/ssaa.c \
	rendering/supersampling/aa_utils.c \
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
SPEED_FLAGS := -O3 -march=native
LDFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer
CFLAGS := -Wall -Wextra -Werror -Wunused-function \
	-I$(INC_DIR) -Isrc/my_libft/headers \
	$(SPEED_FLAGS) -g \


NAME := miniRT

all: $(NAME)
# -Isrc/my_libft/headers
$(NAME): $(LIBFT) $(OBJ) $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIB) \
	-Imlx -I$(MLX_DIR)/includes \
	-lm -lSDL2 -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C src/my_libft

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_DIR):
	@git clone $(MLX_REPO) $(MLX_DIR)

# debug:  $(LIBFT) $(OBJ) $(MLX_DIR)
# 	$(CC) $(DEBUG_FLAGS) $(OBJ) $(LIBFT) -Isrc/my_libft/headers $(MLX_LIB) -Imlx -lm -lSDL2 -I$(MLX_DIR)/includes -o $(NAME)

clean:
	@$(MAKE) clean -C src/my_libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C src/my_libft

re: fclean all

.PHONY: all clean fclean re
