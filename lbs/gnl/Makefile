# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:14:14 by psmolin           #+#    #+#              #
#    Updated: 2025/09/30 18:53:50 by nmikuka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = @cc
RM = @rm -f
CFLAGS = -Wall -Wextra -Werror -I.

NAME = libgnl.a

SRCS = get_next_line.c \
		get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
HEADERS = get_next_line.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
#
.PHONY: all clean fclean re