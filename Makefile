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
OBJ_DIR = obj/
SRC_DIR = src/
INCLUDES = includes

NAME := cub3D

MLX42_DIR := MLX42
MLX42_LIB := $(MLX_DIR)/libmlx42.a
MLX42_REPO := https://github.com/codam-coding-college/MLX42.git

# Compiler and flags
CC := @cc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES)  -I$(MLX42_DIR)/include
RM = rm -f
RMD = rm -rf
MK = make -C

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLXFLAGS := -L$(MLX42_DIR) -lmlx42 -lglfw -ldl -lGL -lm -pthread
endif
ifeq ($(UNAME_S),Darwin)
	MLXFLAGS := -L$(MLX42_DIR) -lmlx42 -lglfw -framework OpenGL -framework AppKit
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
				init_check.c \
        init_checkmap.c \
				init_data.c \
				init_fillmap.c \
				main.c \
				sys_errors.c \
				sys_gamestate.c \
				sys_lib.c \
				draw.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Headers
HEADERS = $(INCLUDES)/cub3d.h

# Extra libs
GNL_DIR = lbs/gnl/
GNL_LIB = $(GNL_DIR)libgnl.a
GNL_FLAGS = -L$(GNL_DIR) -lgnl

#
all: checkMLX makeextra $(NAME)

makeextra:
	$(MK) $(GNL_DIR) all

$(NAME): $(OBJS) $(MLX42_DIR)/libmlx42.a
	$(CC) $(CFLAGS) $(OBJS) $(GNL_FLAGS) $(MLXFLAGS) -o $@ 
	@echo "$(COL_G)Project complied successfully!$(COL_X)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX42_DIR)/libmlx42.a:
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
	@if [ ! -f "$(MLX42_DIR)/libmlx42.a" ]; then \
		echo "Building MLX42 library..."; \
		cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build; \
		cmake --build $(MLX42_DIR)/build; \
		cp $(MLX42_DIR)/build/libmlx42.a $(MLX42_DIR)/; \
	else \
		echo "MLX42 library already built."; \
	fi

clean:
	@$(RM) $(OBJ_FILES)
	@$(MK) $(GNL_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(RMD) $(MLX42_DIR)
	@$(MK) $(GNL_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re
