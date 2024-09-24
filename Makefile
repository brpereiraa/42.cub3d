# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bruno <bruno@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 11:09:52 by bruno             #+#    #+#              #
#    Updated: 2024/09/24 17:29:14 by bruno            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror
SRC = ./src/main.c ./src/validations.c

OBJS = $(SRC:.c=.o)
LIBFT = libft
LIBFT_N = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) --no-print-directory -C $(LIBFT)
	cc -g $(OBJS) $(CFLAGS) $(LIBFT_N) -o $(NAME)

clean:
	$(MAKE) --no-print-directory -C $(LIBFT) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) --no-print-directory -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: