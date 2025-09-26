# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 11:32:00 by nmikuka           #+#    #+#              #
#    Updated: 2025/09/26 11:50:33 by nmikuka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_DIR := obj

# Compiler and flags
CC := @cc
CFLAGS := -Wall -Wextra -Werror

NAME := cub3D

MLX42_DIR = MLX42
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git

# Source and object files
SRC_FILES := main.c
OBJ_FILES := $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(MLX42_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX42_DIR):
	@echo "Checking for MLX42..."
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		echo "Cloning MLX42 into $(MLX42_DIR)..."; \
		git clone $(MLX42_REPO) $(MLX42_DIR); \
	else \
		echo "MLX42 already exists in $(MLX42_DIR). Skipping clone."; \
	fi

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re