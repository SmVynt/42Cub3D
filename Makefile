# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 13:11:09 by psmolin           #+#    #+#              #
#    Updated: 2025/10/30 12:43:06 by psmolin          ###   ########.fr        #
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
				game_loop.c \
				init_check.c \
				init_checkmap.c \
				init_data.c \
				init_fillmap.c \
				init_game.c \
				init_hooks.c \
				init_key_hooks.c \
				init_textures.c \
				main.c \
				render_draw.c \
				render_images.c \
				render_minimap.c \
				render_raycast.c \
				render_ui.c \
				sys_clean.c \
				sys_errors.c \
				sys_gamestate.c \
				sys_lib.c \
				sys_math.c \
				sys_utils.c \
				ft_mat4.c \
				ft_mat4_transform.c \
				ft_list.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Headers
HEADERS = $(INCLUDES)/cub3d.h \
			$(INCLUDES)/structs.h \
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

.PHONY: all clean fclean re
