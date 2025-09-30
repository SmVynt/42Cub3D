# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 13:11:09 by psmolin           #+#    #+#              #
#    Updated: 2025/09/30 10:05:53 by nmikuka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_DIR := obj/
SRC_DIR := src/
INCLUDES := includes

NAME := cub3D

MLX42_DIR := MLX42
MLX42_LIB := $(MLX_DIR)/libmlx42.a
MLX42_REPO := https://github.com/codam-coding-college/MLX42.git

# Compiler and flags
CC := @cc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES)  -I$(MLX42_DIR)/include


UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLXFLAGS := -L$(MLX42_DIR) -lmlx42 -lglfw -ldl -lGL -lm -pthread
endif
ifeq ($(UNAME_S),Darwin)
	MLXFLAGS := -L$(MLX42_DIR) -lmlx42 -lglfw -framework OpenGL -framework AppKit
endif

# Source and object files
SRC_FILES	= \
				init_check.c \
				main.c \
				sys_errors.c \
				sys_gamestate.c \
				sys_lib.c \
				draw.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Headers
HEADERS = $(INCLUDES)/cub3d.h

all: $(NAME)

$(NAME): $(OBJS) $(MLX42_DIR)/libmlx42.a
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(MLXFLAGS)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX42_DIR)/libmlx42.a:
	@echo "Checking for MLX42..."
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		echo "Cloning MLX42 into $(MLX42_DIR)..."; \
		git clone $(MLX42_REPO) $(MLX42_DIR); \
	else \
		echo "MLX42 already exists in $(MLX42_DIR). Skipping clone."; \
	fi
	@if [ ! -f "$(MLX42_DIR)/libmlx42.a" ]; then \
		echo "Building MLX42 library..."; \
		cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build; \
		cmake --build $(MLX42_DIR)/build; \
		cp $(MLX42_DIR)/build/libmlx42.a $(MLX42_DIR)/; \
	else \
		echo "MLX42 library already built."; \
	fi

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re
