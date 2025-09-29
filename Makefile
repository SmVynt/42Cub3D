# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 13:11:09 by psmolin           #+#    #+#              #
#    Updated: 2025/09/26 17:12:46 by psmolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_DIR = obj/
SRC_DIR = src/
INCLUDES = includes

# Compiler and flags
CC = @cc
RM = rm -f
RMD = rm -rf
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES)

NAME = cub3D

MLX42_DIR = MLX42
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git

# Colors
COL_X		= \033[0m
COL_R		= \033[1;31m
COL_G		= \033[1;32m
COL_Y		= \033[1;33m
COL_B		= \033[1;34m
COL_C		= \033[1;36m

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

all: checkMLX $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@
	@echo "$(COL_G)Project complied successfully!$(COL_X)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

checkMLX:
	@echo "$(COL_B)Checking for MLX42...$(COL_X)"
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		echo "$(COL_B)Cloning MLX42 into $(MLX42_DIR)...$(COL_X)"; \
		git clone $(MLX42_REPO) $(MLX42_DIR) &&\
		cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR) &&\
		make -C $(MLX42_DIR)/build; \
		if [ $$? -ne 0]; then \
			echo "$(COL_R)MLX failed to build$(COL_X)"; \
			exit 1; \
		fi; \
		echo "$(COL_G)MLX installed$(COL_X)"; \
	else \
		echo "$(COL_B)MLX42 already exists in $(MLX42_DIR). Skipping clone.$(COL_X)"; \
	fi

clean:
	@$(RM) $(OBJ_FILES)

fclean: clean
	@$(RM) $(NAME)
	@$(RMD) $(MLX42_DIR)

re: fclean all

bonus: all

.PHONY: all clean fclean re
