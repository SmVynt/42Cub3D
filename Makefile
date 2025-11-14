# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 13:11:09 by psmolin           #+#    #+#              #
#    Updated: 2025/11/14 20:22:06 by nmikuka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_DIR = obj/
SRC_DIR = src/
INCLUDES = includes

NAME := cub3D

MLX42_DIR := MLX42
MLX42_LIB := $(MLX42_DIR)/libmlx42.a
MLX42_REPO := https://github.com/codam-coding-college/MLX42.git

# Compiler and flags
CC := @cc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES)  -I$(MLX42_DIR)/include  -I/opt/homebrew/include

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLXFLAGS := -L$(MLX42_DIR) -lmlx42 -lglfw -ldl -lGL -lm -pthread
endif
ifeq ($(UNAME_S),Darwin)
	MLXFLAGS := -L$(MLX42_DIR) -lmlx42 -L/opt/homebrew/lib -lglfw -framework OpenGL -framework AppKit
endif

# Colors
COL_X		= \033[0m
COL_R		= \033[1;31m
COL_G		= \033[1;32m
COL_Y		= \033[1;33m
COL_B		= \033[1;34m
COL_C		= \033[1;36m

# Source and object files
SRC_FILES	= \
				game_loop_graphics.c \
				game_loop_player.c \
				game_loop_tile_check.c \
				game_loop.c \
				game_doors.c \
				game_chars_alien.c \
				game_chars.c \
				game_items.c \
				game_interact_message.c \
				game_interact.c \
				game_end_screen.c \
				game_player.c \
				init_check_file.c \
				init_check_map.c \
				init_check_tex_colors.c \
				init_data_null.c \
				init_data_prefabs_chars.c \
				init_data_prefabs_doors.c \
				init_data_prefabs_items.c \
				init_data_prefabs.c \
				init_data.c \
				init_fillmap.c \
				init_game_doors.c \
				init_game_items_chars.c \
				init_game_sprites.c \
				init_game_textures_env.c \
				init_game_textures_ui.c \
				init_game.c \
				init_hooks.c \
				init_key_hooks.c \
				init_textures.c \
				main.c \
				render_draw_utils.c \
				render_draw.c \
				render_images.c \
				render_minimap_draw.c \
				render_minimap_utils.c \
				render_minimap.c \
				render_raycast_bg.c \
				render_raycast_ceil_floor.c \
				render_raycast_rayend_door.c \
				render_raycast_rayend.c \
				render_raycast_utils.c \
				render_raycast_wall.c \
				render_raycast.c \
				render_shapes.c \
				render_sprites_calc.c \
				render_sprites_draw.c \
				render_sprites.c \
				render_ui.c \
				sys_clean_mlx.c \
				sys_clean_mlx2.c \
				sys_clean.c \
				sys_errors.c \
				sys_gamestate.c \
				sys_lib.c \
				sys_lib2.c \
				sys_math.c \
				sys_math2.c \
				sys_utils.c \
				ft_mat4.c \
				ft_mat4_transform.c \
				ft_list.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Headers
HEADERS = $(INCLUDES)/cub3d.h \
			$(INCLUDES)/structs.h \
			$(INCLUDES)/ft_mat4.h \
			$(INCLUDES)/bonus_setup.h \
			$(INCLUDES)/libft_mini.h

# Extra libs
GNL_DIR = lib/gnl/
GNL_LIB = $(GNL_DIR)libgnl.a
GNL_FLAGS = -L$(GNL_DIR) -lgnl

#
all: $(NAME)

makeextra:
	@make -s -C $(GNL_DIR) all

$(NAME): $(OBJS) $(MLX42_LIB) makeextra
	$(CC) $(CFLAGS) $(OBJS) $(GNL_FLAGS) $(MLXFLAGS) -o $@
	@echo "$(COL_G)Project complied successfully!$(COL_X)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS) $(MLX42_LIB)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX42_LIB):
	@echo "Checking for MLX42..."
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		echo "Cloning MLX42 into $(MLX42_DIR)..."; \
		git clone $(MLX42_REPO) $(MLX42_DIR); \
	else \
		echo "MLX42 already exists in $(MLX42_DIR). Skipping clone."; \
	fi
	@if [ ! -f "$(MLX42_LIB)" ]; then \
		echo "Building MLX42 library..."; \
		cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build; \
		cmake --build $(MLX42_DIR)/build; \
		cp $(MLX42_DIR)/build/libmlx42.a $(MLX42_DIR)/; \
	else \
		echo "MLX42 library already built."; \
	fi

clean:
	@rm -f $(OBJS)
	@make -s -C $(GNL_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(GNL_DIR) fclean

re: fclean all

bonus: all

norm:
	norminette $(SRC_DIR)
	norminette $(INCLUDES)/

.PHONY: all clean fclean re bonus norm
