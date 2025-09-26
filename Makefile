# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 13:11:09 by psmolin           #+#    #+#              #
#    Updated: 2025/09/26 14:04:59 by psmolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_DIR := obj/
SRC_DIR := src/
INCLUDES := includes

# Compiler and flags
CC := @cc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES)

NAME := cub3D

MLX42_DIR = MLX42
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git

# Source and object files
SRC_FILES	= \
				$(SRC_DIR)init_check.c \
				$(SRC_DIR)main.c \
				$(SRC_DIR)sys_errors.c \
				$(SRC_DIR)sys_gamestate.c \
				$(SRC_DIR)sys_lib.c
OBJ_FILES	= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

# Headers
HEADERS = $(INCLUDES)/cub3d.h

all: $(NAME)

$(NAME): $(OBJ_FILES) $(MLX42_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
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
