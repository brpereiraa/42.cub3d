# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 11:09:52 by bruno             #+#    #+#              #
#    Updated: 2024/11/01 17:36:52 by brpereir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

MLXFLAGS = -L ./mlx -lmlx -Ilmlx -lXext -lX11 
CFLAGS = -Wall -Wextra -Werror -I
SRC = ./src/main.c ./src/map.c ./src/mlx.c

OBJS = $(SRC:.c=.o)
LIBFT = libft
LIBFT_N = libft/libft.a

DOWNLOAD = https://cdn.intra.42.fr/document/document/25858/minilibx-linux.tgz
MLX = ./minilibx-linux

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) --no-print-directory -C $(LIBFT)
	$(MAKE) $(MLX)
	cc -g $(OBJS) $(CFLAGS) $(MLXFLAGS) $(LIBFT_N) -o $(NAME)

update:
	@if [ ! -d $(MLX) ]; then \
		echo " Downloading mlx..."; \
		mkdir -p $(MLX); \
		wget $(DOWNLOAD) -O "./minilibx-linux.tgz"; \
		tar -xzvf "./minilibx-linux.tgz" -C .; \
		rm -fr "./minilibx-linux.tgz"; \
	else \
		echo "Folder already exists"; \
	fi

uclean:
	rm -fr $(MLX)

clean:
	$(MAKE) --no-print-directory -C $(LIBFT) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) --no-print-directory -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.SILENT:	

.PHONY: all clean fclean re

